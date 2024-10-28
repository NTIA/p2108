/** @file Driver.h
 * Interface header for this driver executable
 */
#pragma once

#include "CommaSeparatedIterator.h"
#include "ITS.ITU.PSeries.P2108/P2108.h"
#include "ReturnCodes.h"
#include "Structs.h"

#include <fstream>   // for std::ifstream, std::ofstream
#include <iomanip>   // for std::setw
#include <iostream>  // for std::cerr, std::cout, std::ostream
#include <ostream>   // for std::endl
#include <string>    // for std::string, std::stoi, std::stod
#include <tuple>     // for std::tie
#include <vector>    // for std::vector

/////////////////////////////
// Macros

/** Shortcut for concise print-to-file statements in driver */
#define PRINT << std::endl << std::left << std::setw(25) <<
/** Shortcut for setting fixed whitespace padding in driver file output */
#define SETW13 << std::setw(13) <<

//////////////////////////////
// Library Namespace
using namespace ITS::ITU::PSeries::P2108;

/////////////////////////////
// Functions
DrvrReturnCode ParseArguments(int argc, char **argv, DrvrParams &params);
void Help(std::ostream &os = std::cout);
DrvrReturnCode ValidateInputs(const DrvrParams &params);

// Aeronautical Statistical Model
ReturnCode CallAeronauticalStatisticalModel(
    ASMParams &asm_params, std::vector<double> &L_ces__db
);
DrvrReturnCode
    ParseASMInputFile(const std::string &in_file, ASMParams &asm_params);
void WriteASMInputs(std::ofstream &fp, const ASMParams &params);

// Height Gain Terminal Correction Model
ReturnCode CallHeightGainTerminalCorrectionModel(
    HGTCMParams &hgtc_params, std::vector<double> &A_h__db
);
DrvrReturnCode
    ParseHGTCInputFile(const std::string &in_file, HGTCMParams &hgtc_params);
void WriteHGTCInputs(std::ofstream &fp, const HGTCMParams &params);

// Terrestrial Statistical Model
ReturnCode CallTerrestrialStatisticalModel(
    TSMParams &tsm_params, std::vector<double> &L_ctt__db
);
DrvrReturnCode
    ParseTSMInputFile(const std::string &in_file, TSMParams &tsm_params);
void WriteTSMInputs(std::ofstream &fp, const TSMParams &params);

// Reporting
void PrintClutterTypeLabel(std::ofstream &fp, const ClutterType clutter_type);
void PrintLabel(std::ofstream &fp, std::string &lbl);

// Driver Utils
void Version(std::ostream &os = std::cout);
DrvrReturnCode ParseInteger(const std::string &str, int &value);
DrvrReturnCode ParseDouble(const std::string &str, double &value);
std::string GetDatetimeString();
void StringToLower(std::string &str);
