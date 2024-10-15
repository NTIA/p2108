/** @file main.cpp
 * Implements the main function of the executable, and other high-level functions
 */
#include "Driver.h"
#include "Labels.h"
#include "Tags.h"

/*******************************************************************************
 * Main function of the driver executable
 ******************************************************************************/
int main(int argc, char **argv) {
    int rtn;
    DrvrParams params;

    // Parse command line arguments
    rtn = ParseArguments(argc, argv, params);
    if (rtn == DRVR__RETURN_SUCCESS)
        return SUCCESS;
    if (rtn) {
        Help();
        return rtn;
    }

    // validate command line inputs
    rtn = ValidateInputs(params);
    if (rtn) {
        Help();
        return rtn;
    }

    // Initialize model inputs/outputs
    HGTCParams hgtc_params;
    TSMParams tsm_params;
    ASMParams asm_params;
    std::vector<double> loss__db;  // Use for any model

    switch (params.model) {
        case P2108Model::HGTCM:
            rtn = CallHeightGainTerminalCorrectionModel(
                params, hgtc_params, loss__db
            );
            break;
        case P2108Model::TSM:
            rtn = CallTerrestrialStatisticalModel(params, tsm_params, loss__db);
            break;
        case P2108Model::ASM:
            rtn = CallAeronauticalStatisticalModel(
                params, asm_params, loss__db
            );
            break;
        default:
            rtn = DRVRERR__VALIDATION_MODEL;
    }

    // Return driver error code if one was returned
    if (rtn >= 1100)
        return rtn;

    // Print results to file
    std::ofstream fp;
    fp.open(params.out_file.c_str());
    if (!fp.is_open()) {
        std::cerr << "Error opening output file. Exiting." << std::endl;
        return DRVRERR__OPENING_OUTPUT_FILE;
    }
    fp << std::left << std::setw(25) << "Model" << LIBRARY_NAME;
    fp PRINT "Model Variant";
    switch (params.model) {
        case P2108Model::HGTCM:
            fp << LBL__HGTCM;
            break;
        case P2108Model::TSM:
            fp << LBL__TSM;
            break;
        case P2108Model::ASM:
            fp << LBL__ASM;
            break;
            // Validation above ensures one of these cases evaluates
    }
    fp PRINT "Library Version" << "v" << LIBRARY_VERSION;
    fp PRINT "Driver Version" << "v" << DRIVER_VERSION;
    fp PRINT "Date Generated" << GetDatetimeString();
    fp PRINT "Input Arguments";
    for (int i = 1; i < argc; i++) {
        fp << argv[i] << " ";
    }
    fp << std::endl << std::endl;
    fp << "Inputs";

    switch (params.model) {
        case P2108Model::HGTCM:
            WriteHGTCInputs(fp, hgtc_params);
            break;
        case P2108Model::TSM:
            WriteTSMInputs(fp, tsm_params);
            break;
        case P2108Model::ASM:
            WriteASMInputs(fp, asm_params);
            break;
            // Validation above ensures one of these cases evaluates
    }

    if (rtn != SUCCESS) {
        fp PRINT LIBRARY_NAME << " Error" SETW13 rtn;
        PrintErrorMsgLabel(fp, rtn);
    } else {
        fp << std::endl << std::endl << "Results";
        fp PRINT "Return Code" SETW13 rtn;
        PrintErrorMsgLabel(fp, rtn);
        fp PRINT "Clutter loss" SETW13 std::fixed
            << std::setprecision(1) << loss__db.front() << UNITS__DB;
    }
    fp.close();
    return SUCCESS;
}

/*******************************************************************************
 * Parse the command line arguments
 * 
 * @param[in]  argc    Number of arguments
 * @param[in]  argv    Command line arguments
 * @param[out] params  Structure with user input params
 * @return             Return code
 ******************************************************************************/
int ParseArguments(int argc, char **argv, DrvrParams &params) {
    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        std::transform(arg.begin(), arg.end(), arg.begin(), [](const char c) {
            return static_cast<char>(std::tolower(c));
        });

        if (arg == "-i") {
            params.in_file = argv[i + 1];
            i++;
        } else if (arg == "-o") {
            params.out_file = argv[i + 1];
            i++;
        } else if (arg == "-model") {
            std::string argval(argv[i + 1]);
            std::transform(
                argval.begin(),
                argval.end(),
                argval.begin(),
                [](const char c) { return static_cast<char>(std::tolower(c)); }
            );
            if (argval == "asm") {
                params.model = P2108Model::ASM;
            } else if (argval == "hgtcm") {
                params.model = P2108Model::HGTCM;
            } else if (argval == "tsm") {
                params.model = P2108Model::TSM;
            } else {
                params.model = P2108Model::NOT_SET;
            }
            i++;
        } else if (arg == "-v") {
            Version();
            return DRVR__RETURN_SUCCESS;
        } else if (arg == "-h") {
            Help();
            return DRVR__RETURN_SUCCESS;
        } else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            return DRVRERR__INVALID_OPTION;
        }
    }

    return SUCCESS;
}

/*******************************************************************************
 * Print help instructions to the terminal
 * 
 * @param[in] os  Output stream for writing; defaults to `std::cout`
 ******************************************************************************/
void Help(std::ostream &os) {
    os << std::endl << "Usage: .\\<Driver Executable> [Options]" << std::endl;
    os << "Options (not case sensitive)" << std::endl;
    os << "\t-i      :: Input file name" << std::endl;
    os << "\t-o      :: Output file name" << std::endl;
    os << "\t-model  :: Model to run [HGTCM, TSM, ASM]" << std::endl;
    os << std::endl << "Examples:" << std::endl;
    os << "\t[WINDOWS] " << DRIVER_NAME
       << ".exe -i inputs.txt -o results.txt -model ASM" << std::endl;
    os << "\t[LINUX]   .\\" << DRIVER_NAME
       << " -i inputs.txt -o results.txt -model ASM" << std::endl;
    os << std::endl;
};

/*******************************************************************************
 * Validate that required inputs are present for the mode specified by the user.
 * 
 * This function DOES NOT check the validity of the parameter values, only that
 * required parameters have been specified by the user
 * 
 * @param[in] params  Structure with user input parameters
 * @return            Return code
 ******************************************************************************/
int ValidateInputs(const DrvrParams &params) {
    if (params.in_file.length() == 0)
        return Validate_RequiredErrMsgHelper("-i", DRVRERR__VALIDATION_IN_FILE);

    if (params.out_file.length() == 0)
        return Validate_RequiredErrMsgHelper(
            "-o", DRVRERR__VALIDATION_OUT_FILE
        );

    if (params.model == P2108Model::NOT_SET)
        return Validate_RequiredErrMsgHelper(
            "-model", DRVRERR__VALIDATION_MODEL
        );

    return SUCCESS;
}
