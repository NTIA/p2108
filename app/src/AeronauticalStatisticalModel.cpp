/** @file AeronauticalStatisticalModel.cpp
 * Implements top-level functions for running the Aeronautical Statistical Model.
 */
#include "Driver.h"
#include "Tags.h"


/*******************************************************************************
 * Top-level control function for Aeronautical Statistical Model operation
 * 
 * @param[in] asm_params  Aeronautical Statistical Model input parameter struct
 * @param[out] L_ces__db   Basic transmission loss, in dB
 * @return                 Return code
 ******************************************************************************/
int CallAeronauticalStatisticalModel(
    ASMParams &asm_params, std::vector<double> &L_ces__db
) {
    int rtn;
    double L_ces;
    rtn = AeronauticalStatisticalModel(
        asm_params.f__ghz, asm_params.theta__deg, asm_params.p, L_ces
    );
    L_ces__db.push_back(L_ces);

    return rtn;
}

/*******************************************************************************
 * Parse input stream (file or string stream) to ASM parameter struct.
 * 
 * @param[in]  stream      Path to ASM input parameter file
 * @param[out] asm_params  ASM input parameter struct
 * @return                 Return code
 ******************************************************************************/
int ParseASMInputStream(std::istream &stream, ASMParams &asm_params) {
    CommaSeparatedIterator it(stream);
    std::string key, value;
    while (it) {
        std::tie(key, value) = *it;
        if (key.compare(TAG__FREQ) == 0) {
            if (ParseDouble(value, asm_params.f__ghz) == DRVRERR__PARSE) {
                return ParsingErrorHelper(DRVRERR__PARSE_FREQ, TAG__FREQ);
            }
        } else if (key.compare(TAG__THETA) == 0) {
            if (ParseDouble(value, asm_params.theta__deg) == DRVRERR__PARSE) {
                return ParsingErrorHelper(DRVRERR__PARSE_THETA, TAG__THETA);
            }
        } else if (key.compare(TAG__PERCENTAGE) == 0) {
            if (ParseDouble(value, asm_params.p) == DRVRERR__PARSE) {
                return ParsingErrorHelper(
                    DRVRERR__PARSE_PERCENTAGE, TAG__PERCENTAGE
                );
            }
        } else {
            std::cerr << "Driver Error " << DRVRERR__PARSE;
            std::cerr << ": Unknown input parameter '" << key << "'"
                      << std::endl;
            return DRVRERR__PARSE;
        }
        ++it;
    }
    return SUCCESS;
}

/*******************************************************************************
 * Parse Aeronautical Statistical Model input parameter file
 * 
 * @param[in]  in_file     Path to ASM input parameter file
 * @param[out] asm_params  ASM input parameter struct
 * @return                 Return code
 ******************************************************************************/
int ParseASMInputFile(const std::string &in_file, ASMParams &asm_params) {
    std::ifstream file(in_file);
    if (!file) {
        std::cerr << "Failed to open file " << in_file << std::endl;
        return DRVRERR__OPENING_INPUT_FILE;
    }
    return ParseASMInputStream(file, asm_params);
}

/*******************************************************************************
 * Write Aeronautical Statistical Model inputs to the report file
 * 
 * @param[in] fp      Output stream, a text file open for writing
 * @param[in] params  ASM input parameter struct
 ******************************************************************************/
void WriteASMInputs(std::ofstream &fp, const ASMParams &params) {
    fp PRINT TAG__FREQ SETW13 params.f__ghz << UNITS__GHZ;
    fp PRINT TAG__THETA SETW13 params.theta__deg << UNITS__DEGREES;
    fp PRINT TAG__PERCENTAGE SETW13 params.p << UNITS__PERCENT;
}