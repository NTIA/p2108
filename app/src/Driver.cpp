/** @file Driver.cpp
 * Implements the main function of the executable, and other high-level functions
 */
#include "Driver.h"

#include <algorithm>  // for std::find

/*******************************************************************************
 * Main function of the driver executable
 * 
 * @param[in] argc  Number of arguments entered on the command line
 * @param[in] argv  Array containing the provided command-line arguments
 * @return          Return code
 ******************************************************************************/
int main(int argc, char **argv) {
    int rtn;
    DrvrParams params;

    // Parse command line arguments
    rtn = ParseArguments(argc, argv, params);
    if (rtn == DRVR__RETURN_SUCCESS) {
        return SUCCESS;
    } else if (rtn != DRVR__SUCCESS) {
        Help();
        return rtn;
    }

    // Ensure required options were provided
    rtn = ValidateInputs(params);
    if (rtn != DRVR__SUCCESS) {
        Help();
        return rtn;
    }

    // Initialize model inputs/outputs
    HGTCMParams hgtcm_params;
    TSMParams tsm_params;
    ASMParams asm_params;
    std::vector<double> loss__db;  // Use for any model

    switch (params.model) {
        case P2108Model::HGTCM:
            rtn = ParseHGTCMInputFile(params.in_file, hgtcm_params);
            if (rtn != DRVR__SUCCESS) {
                return rtn;
            }
            rtn = CallHeightGainTerminalCorrectionModel(hgtcm_params, loss__db);
            break;
        case P2108Model::TSM:
            rtn = ParseTSMInputFile(params.in_file, tsm_params);
            if (rtn != DRVR__SUCCESS) {
                return rtn;
            }
            rtn = CallTerrestrialStatisticalModel(tsm_params, loss__db);
            break;
        case P2108Model::ASM:
            rtn = ParseASMInputFile(params.in_file, asm_params);
            if (rtn != DRVR__SUCCESS) {
                return rtn;
            }
            rtn = CallAeronauticalStatisticalModel(asm_params, loss__db);
            break;
        default:
            rtn = DRVRERR__VALIDATION_MODEL;
    }

    // Return driver error code if one was returned
    if (rtn > DRVR__RETURN_SUCCESS) {
        std::cerr << GetDrvrReturnStatus(rtn);
        return rtn;
    }

    // Print results to file
    std::ofstream fp(params.out_file);
    if (!fp) {
        std::cerr << "Error opening output file. Exiting." << std::endl;
        return DRVRERR__OPENING_OUTPUT_FILE;
    }
    fp << std::left << std::setw(25) << "Model" << LIBRARY_NAME;
    fp PRINT "Model Variant";
    switch (params.model) {
        case P2108Model::HGTCM:
            fp << "Height Gain Terminal Correction Model";
            break;
        case P2108Model::TSM:
            fp << "Terrestrial Statistical Model";
            break;
        case P2108Model::ASM:
            fp << "Aeronautical Statistical Model";
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
            WriteHGTCMInputs(fp, hgtcm_params);
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
        PrintLabel(fp, GetReturnStatus(rtn));
    } else {
        fp << std::endl << std::endl << "Results";
        fp PRINT "Return Code" SETW13 rtn;
        PrintLabel(fp, GetReturnStatus(rtn));
        fp PRINT "Clutter loss" SETW13 std::fixed << std::setprecision(1)
                                                  << loss__db.front() << "(dB)";
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
DrvrReturnCode ParseArguments(int argc, char **argv, DrvrParams &params) {
    const std::vector<std::string> validArgs
        = {"-i", "-o", "-model", "-h", "--help", "-v", "--version"};

    for (int i = 1; i < argc; i++) {
        // Parse arg to lowercase string
        std::string arg(argv[i]);
        StringToLower(arg);

        // Check if provided flag is valid
        if (std::find(validArgs.begin(), validArgs.end(), arg)
            == validArgs.end()) {
            // Invalid argument provided
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            return DRVRERR__INVALID_OPTION;
        }

        // Handle simple flags which don't have associated values (e.g., "-v", "-DBG")
        if (arg == "-v" || arg == "--version") {
            Version();
            return DRVR__RETURN_SUCCESS;
        } else if (arg == "-h" || arg == "--help") {
            Help();
            return DRVR__RETURN_SUCCESS;
        }

        // Check if end of arguments reached or next argument is another flag
        if (i + 1 >= argc || argv[i + 1][0] == '-') {
            std::cerr << "Error: no value given for " << arg << std::endl;
            return DRVRERR__MISSING_OPTION;
        }

        // Handle inputs which provide values (e.g. "-i in.txt").
        if (arg == "-i") {
            params.in_file = argv[i + 1];
            i++;
        } else if (arg == "-o") {
            params.out_file = argv[i + 1];
            i++;
        } else if (arg == "-model") {
            std::string argval(argv[i + 1]);
            StringToLower(argval);
            if (argval == "asm") {
                params.model = P2108Model::ASM;
            } else if (argval == "hgtcm") {
                params.model = P2108Model::HGTCM;
            } else if (argval == "tsm") {
                params.model = P2108Model::TSM;
            }
            i++;
        }
    }

    return DRVR__SUCCESS;
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
       << ".exe -i inputs.txt -model ASM -o results.txt" << std::endl;
    os << "\t[LINUX]   .\\" << DRIVER_NAME
       << " -i in.txt -model ASM -o results.txt" << std::endl;
    os << "Other Options (which don't run the model)" << std::endl;
    os << "\t-h      :: Display this help message" << std::endl;
    os << "\t-v      :: Display program version information" << std::endl;
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
DrvrReturnCode ValidateInputs(const DrvrParams &params) {
    DrvrParams not_set;
    DrvrReturnCode rtn = DRVR__SUCCESS;
    if (params.in_file == not_set.in_file)
        rtn = DRVRERR__VALIDATION_IN_FILE;
    if (params.out_file == not_set.out_file)
        rtn = DRVRERR__VALIDATION_OUT_FILE;
    if (params.model == not_set.model)
        rtn = DRVRERR__VALIDATION_MODEL;

    if (rtn != DRVR__SUCCESS)
        std::cerr << GetDrvrReturnStatus(rtn);

    return rtn;
}