/** @file TerrestrialStatisticalModel.cpp
 * Implements top-level functions for running the Terrestrial Statistical Model.
 */
#include "Driver.h"
#include "Tags.h"


/*******************************************************************************
 * Top-level control function for Terrestrial Statistical Model operation
 * 
 * @param[in]  params      Driver input parameter struct
 * @param[out] tsm_params  Terrestrial Statistical Model input parameter struct
 * @param[out] L_ctt__db   Additional loss (clutter loss), in dB
 * @return                 Return code
 ******************************************************************************/
int CallTerrestrialStatisticalModel(
    const DrvrParams &params,
    TSMParams &tsm_params,
    std::vector<double> &L_ctt__db
) {
    // Parse input file and populate tsm_params struct
    int rtn = ParseTSMInputFile(params.in_file, tsm_params);
    if (rtn != SUCCESS) {
        return rtn;
    }

    double L_ctt;
    rtn = TerrestrialStatisticalModel(
        tsm_params.f__ghz, tsm_params.d__km, tsm_params.p, L_ctt
    );
    L_ctt__db.push_back(L_ctt);

    return rtn;
}

/*******************************************************************************
 * Parse Terrestrial Statistical Model input parameter file
 * 
 * @param[in]  in_file     Path to TSM input parameter file
 * @param[out] tsm_params  TSM input parameter struct
 * @return                 Return code
 ******************************************************************************/
int ParseTSMInputFile(const std::string &in_file, TSMParams &tsm_params) {
    std::ifstream file;
    file.open(in_file.c_str());
    std::string line;

    while (std::getline(file, line)) {
        size_t i = line.find(",");

        std::string key = line.substr(0, i);
        std::string value = line.substr(i + 1);

        std::transform(key.begin(), key.end(), key.begin(), [](const char c) {
            return static_cast<char>(std::tolower(c));
        });

        if (key.compare(TAG__FREQ) == 0) {
            if (ParseDouble(value, tsm_params.f__ghz) == DRVRERR__PARSE) {
                return ParsingErrorHelper(DRVRERR__PARSE_FREQ, TAG__FREQ);
            }
        } else if (key.compare(TAG__PATH_DIST) == 0) {
            if (ParseDouble(value, tsm_params.d__km) == DRVRERR__PARSE) {
                return ParsingErrorHelper(
                    DRVRERR__PARSE_PATH_DIST, TAG__PATH_DIST
                );
            }
        } else if (key.compare(TAG__PERCENTAGE) == 0) {
            if (ParseDouble(value, tsm_params.p) == DRVRERR__PARSE) {
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
    }
    file.close();
    return SUCCESS;
}

/*******************************************************************************
 * Write Terrestrial Statistical Model inputs to the report file
 * 
 * @param[in] fp          Output stream, a text file open for writing
 * @param[in] tsm_params  TSM input parameter struct
 ******************************************************************************/
void WriteTSMInputs(std::ofstream &fp, const TSMParams &params) {
    fp PRINT TAG__FREQ SETW13 params.f__ghz << UNITS__GHZ;
    fp PRINT TAG__THETA SETW13 params.d__km << UNITS__KM;
    fp PRINT TAG__PERCENTAGE SETW13 params.p << UNITS__PERCENT;
}