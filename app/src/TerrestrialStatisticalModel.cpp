/** @file TerrestrialStatisticalModel.cpp
 * Implements top-level functions for running the Terrestrial Statistical Model.
 */
#include "Driver.h"

#include <fstream>   // for std::ifstream, std::ofstream
#include <iostream>  // for std::cerr
#include <istream>   // for std::istream
#include <ostream>   // for std::endl
#include <string>    // for std::string
#include <tuple>     // for std::tie
#include <vector>    // for std::vector

// Define the input keys
const std::string TSMInputKeys::f__ghz = "f__ghz";
const std::string TSMInputKeys::d__km = "d__km";
const std::string TSMInputKeys::p = "p";

/*******************************************************************************
 * Top-level control function for Terrestrial Statistical Model operation
 * 
 * @param[in]  tsm_params  Terrestrial Statistical Model input parameter struct
 * @param[out] L_ctt__db   Additional loss (clutter loss), in dB
 * @return                 Return code
 ******************************************************************************/
ReturnCode CallTerrestrialStatisticalModel(
    TSMParams &tsm_params, std::vector<double> &L_ctt__db
) {
    ReturnCode rtn;
    double L_ctt;
    rtn = TerrestrialStatisticalModel(
        tsm_params.f__ghz, tsm_params.d__km, tsm_params.p, L_ctt
    );
    L_ctt__db.push_back(L_ctt);

    return rtn;
}

/*******************************************************************************
 * Parse input stream (file or string stream) to TSM parameter struct.
 * 
 * @param[in]  stream      Input stream containing TSM parameters
 * @param[out] tsm_params  TSM input parameter struct
 * @return                 Return code
 ******************************************************************************/
DrvrReturnCode
    ParseTSMInputStream(std::istream &stream, TSMParams &tsm_params) {
    CommaSeparatedIterator it(stream);
    DrvrReturnCode rtn = DRVR__SUCCESS;
    std::string key, value;
    while (it) {
        std::tie(key, value) = *it;
        if (key.compare(TSMInputKeys::f__ghz) == 0) {
            rtn = ParseDouble(value, tsm_params.f__ghz);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_FREQ;
        } else if (key.compare(TSMInputKeys::d__km) == 0) {
            rtn = ParseDouble(value, tsm_params.d__km);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_PATH_DIST;
        } else if (key.compare(TSMInputKeys::p) == 0) {
            rtn = ParseDouble(value, tsm_params.p);
            if (rtn == DRVRERR__PARSE)
                rtn = DRVRERR__PARSE_PERCENTAGE;
        } else {
            std::cerr << "Unknown parameter: " << key << std::endl;
            rtn = DRVRERR__PARSE;
        }

        if (rtn != DRVR__SUCCESS) {
            std::cerr << GetDrvrReturnStatusMsg(rtn) << std::endl;
            return rtn;
        }
        ++it;
    }
    return rtn;
}

/*******************************************************************************
 * Parse Terrestrial Statistical Model input parameter file
 * 
 * @param[in]  in_file     Path to TSM input parameter file
 * @param[out] tsm_params  TSM input parameter struct
 * @return                 Return code
 ******************************************************************************/
DrvrReturnCode
    ParseTSMInputFile(const std::string &in_file, TSMParams &tsm_params) {
    std::ifstream file(in_file);
    if (!file) {
        std::cerr << "Failed to open file " << in_file << std::endl;
        return DRVRERR__OPENING_INPUT_FILE;
    }
    return ParseTSMInputStream(file, tsm_params);
}

/*******************************************************************************
 * Write Terrestrial Statistical Model inputs to the report file
 * 
 * @param[in] fp      Output stream, a text file open for writing
 * @param[in] params  TSM input parameter struct
 ******************************************************************************/
void WriteTSMInputs(std::ofstream &fp, const TSMParams &params) {
    fp PRINT TSMInputKeys::f__ghz SETW13 params.f__ghz << "(gigahertz)";
    fp PRINT TSMInputKeys::d__km SETW13 params.d__km << "(kilometers)";
    fp PRINT TSMInputKeys::p SETW13 params.p << "(%)";
}