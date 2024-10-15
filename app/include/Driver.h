/** @file Driver.h
 * Interface header for this driver executable
 */
#pragma once

#include "Errors.h"
#include "ITS.ITU.PSeries.P2108/P2108.h"
#include "Structs.h"

#include <algorithm>  // for transform
#include <cctype>     // for tolower
#include <cstring>    // for strlen
#include <ctime>     // for localtime_s, localtime_r, time, time_t, tm, strftime
#include <fstream>   // for ifstream, ofstream
#include <iomanip>   // for setw
#include <iostream>  // for cerr, cout, ostream
#include <string>    // for string, stoi, stod
#include <vector>

/////////////////////////////
// Macros

// Make print-to-file statements more concise in driver
#define PRINT << std::endl << std::left << std::setw(25) <<
#define SETW13 << std::setw(13) <<

using namespace ITS::ITU::PSeries::P2108;

/////////////////////////////
// Functions
int ParseArguments(int argc, char **argv, DrvrParams &params);
void Help(std::ostream &os = std::cout);
int ValidateInputs(const DrvrParams &params);

// Aeronautical Statistical Model
int CallAeronauticalStatisticalModel(
    const DrvrParams &params,
    ASMParams &asm_params,
    std::vector<double> &L_ces__db
);
int ParseASMInputFile(const std::string &in_file, ASMParams &asm_params);
void WriteASMInputs(std::ofstream &fp, const ASMParams &params);

// Height Gain Terminal Correction Model
int CallHeightGainTerminalCorrectionModel(
    const DrvrParams &params,
    HGTCParams &hgtc_params,
    std::vector<double> &A_h__db
);
int ParseHGTCInputFile(const std::string &in_file, HGTCParams &hgtc_params);
void WriteHGTCInputs(std::ofstream &fp, const HGTCParams &params);

// Terrestrial Statistical Model
int CallTerrestrialStatisticalModel(
    const DrvrParams &params,
    TSMParams &tsm_params,
    std::vector<double> &L_ctt__db
);
int ParseTSMInputFile(const std::string &in_file, TSMParams &tsm_params);
void WriteTSMInputs(std::ofstream &fp, const TSMParams &params);

// Reporting
void PrintClutterTypeLabel(std::ofstream &fp, const ClutterType clutter_type);
void PrintErrorMsgLabel(std::ofstream &fp, const int err);
void PrintLabel(std::ofstream &fp, const char *lbl);

// Driver Utils
void Version(std::ostream &os = std::cout);
int Validate_RequiredErrMsgHelper(const std::string &opt, const int err);
int ParseInteger(const std::string &str, int &value);
int ParseDouble(const std::string &str, double &value);
int ParsingErrorHelper(const int err, const std::string &msg);
std::string GetDatetimeString();