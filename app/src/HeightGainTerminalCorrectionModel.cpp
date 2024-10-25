/** @file HeightGainTerminalCorrectionModel.cpp
 * Implements functions for running the Height Gain Terminal Correction Model.
 */
#include "Driver.h"
#include "Tags.h"


/*******************************************************************************
 * Top-level control function for Height Gain Terminal Correction Model
 * 
 * @param[in] hgtc_params  Height Gain Terminal Correction Model input struct
 * @param[out] A_h__db      Additional loss (clutter loss), in dB
 * @return                  Return code
 ******************************************************************************/
int CallHeightGainTerminalCorrectionModel(
    HGTCParams &hgtc_params, std::vector<double> &A_h__db
) {
    int rtn;
    double A_h;
    rtn = HeightGainTerminalCorrectionModel(
        hgtc_params.f__ghz,
        hgtc_params.h__meter,
        hgtc_params.w_s__meter,
        hgtc_params.R__meter,
        hgtc_params.clutter_type,
        A_h
    );
    A_h__db.push_back(A_h);

    return rtn;
}

/*******************************************************************************
 * Parse input stream (file or string stream) to HGTC parameter struct.
 * 
 * @param[in]  stream       Path to ASM input parameter file
 * @param[out] hgtc_params  HGTC input parameter struct
 * @return                  Return code
 ******************************************************************************/
int ParseHGTCInputStream(std::istream &stream, HGTCParams &hgtc_params) {
    CommaSeparatedIterator it(stream);
    std::string key, value;
    while (it) {
        std::tie(key, value) = *it;
        if (key.compare(TAG__FREQ) == 0) {
            if (ParseDouble(value, hgtc_params.f__ghz) == DRVRERR__PARSE) {
                return ParsingErrorHelper(DRVRERR__PARSE_FREQ, TAG__FREQ);
            }
        } else if (key.compare(TAG__HEIGHT) == 0) {
            if (ParseDouble(value, hgtc_params.h__meter) == DRVRERR__PARSE) {
                return ParsingErrorHelper(DRVRERR__PARSE_HEIGHT, TAG__HEIGHT);
            }
        } else if (key.compare(TAG__STREET_WIDTH) == 0) {
            if (ParseDouble(value, hgtc_params.w_s__meter) == DRVRERR__PARSE) {
                return ParsingErrorHelper(
                    DRVRERR__PARSE_STREET_WIDTH, TAG__STREET_WIDTH
                );
            }
        } else if (key.compare(TAG__REPR_HEIGHT) == 0) {
            if (ParseDouble(value, hgtc_params.R__meter) == DRVRERR__PARSE) {
                return ParsingErrorHelper(
                    DRVRERR__PARSE_REPR_HEIGHT, TAG__REPR_HEIGHT
                );
            }
        } else if (key.compare(TAG__CLUTTER_TYPE) == 0) {
            int clutter_type_int;
            if (ParseInteger(value, clutter_type_int) == DRVRERR__PARSE) {
                return ParsingErrorHelper(
                    DRVRERR__PARSE_CLUTTER_TYPE, TAG__CLUTTER_TYPE
                );
            }
            hgtc_params.clutter_type
                = static_cast<ClutterType>(clutter_type_int);
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
 * Parse Height Gain Terminal Correction Model input parameter file
 * 
 * @param[in]  in_file      Path to HGTC input parameter file
 * @param[out] hgtc_params  HGTC input parameter struct
 * @return                  Return code
 ******************************************************************************/
int ParseHGTCInputFile(const std::string &in_file, HGTCParams &hgtc_params) {
    std::ifstream file(in_file);
    if (!file) {
        std::cerr << "Failed to open file " << in_file << std::endl;
        return DRVRERR__OPENING_INPUT_FILE;
    }
    return ParseHGTCInputStream(file, hgtc_params);
}

/*******************************************************************************
 * Write Height Gain Terminal Correction Model inputs to the report file
 * 
 * @param[in] fp      Output stream, a text file open for writing
 * @param[in] params  HGTCM input parameter struct
 ******************************************************************************/
void WriteHGTCInputs(std::ofstream &fp, const HGTCParams &params) {
    fp PRINT TAG__FREQ SETW13 params.f__ghz << UNITS__GHZ;
    fp PRINT TAG__HEIGHT SETW13 params.h__meter << UNITS__METER;
    fp PRINT TAG__STREET_WIDTH SETW13 params.w_s__meter << UNITS__METER;
    fp PRINT TAG__REPR_HEIGHT SETW13 params.R__meter << UNITS__METER;
    fp PRINT TAG__CLUTTER_TYPE SETW13 static_cast<int>(params.clutter_type);
    PrintClutterTypeLabel(fp, params.clutter_type);
}
