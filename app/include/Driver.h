/** @file Driver.h
 * Interface header for this driver executable
 */
#pragma once

#include "CommaSeparatedIterator.h"
#include "P2108.h"
#include "ReturnCodes.h"
#include "Structs.h"

#include <fstream>   // for std::ofstream
#include <iomanip>   // for std::left, std::setw
#include <iostream>  // for std::cout
#include <ostream>   // for std::endl, std::ostream
#include <string>    // for std::string
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
void Help(std::ostream &os = std::cout);
DrvrReturnCode ParseArguments(int argc, char **argv, DrvrParams &params);
DrvrReturnCode ValidateInputs(const DrvrParams &params);

// Aeronautical Statistical Model
ReturnCode CallAeronauticalStatisticalModel(
    ASMParams &asm_params, std::vector<double> &L_ces__db
);
DrvrReturnCode
    ParseASMInputFile(const std::string &in_file, ASMParams &asm_params);
DrvrReturnCode ParseASMInputStream(std::istream &stream, ASMParams &asm_params);
void WriteASMInputs(std::ofstream &fp, const ASMParams &params);

// Height Gain Terminal Correction Model
ReturnCode CallHeightGainTerminalCorrectionModel(
    HGTCMParams &hgtcm_params, std::vector<double> &A_h__db
);
DrvrReturnCode
    ParseHGTCMInputFile(const std::string &in_file, HGTCMParams &hgtcm_params);
DrvrReturnCode
    ParseHGTCMInputStream(std::istream &stream, HGTCMParams &hgtcm_params);
void WriteHGTCMInputs(std::ofstream &fp, const HGTCMParams &params);

// Terrestrial Statistical Model
ReturnCode CallTerrestrialStatisticalModel(
    TSMParams &tsm_params, std::vector<double> &L_ctt__db
);
DrvrReturnCode
    ParseTSMInputFile(const std::string &in_file, TSMParams &tsm_params);
DrvrReturnCode ParseTSMInputStream(std::istream &stream, TSMParams &tsm_params);
void WriteTSMInputs(std::ofstream &fp, const TSMParams &params);

// Reporting
void PrintClutterTypeLabel(std::ofstream &fp, const ClutterType clutter_type);

// Driver Utils
std::string GetDatetimeString();
DrvrReturnCode ParseBoolean(const std::string &str, bool &value);
DrvrReturnCode ParseDouble(const std::string &str, double &value);
DrvrReturnCode ParseInteger(const std::string &str, int &value);
void PrintLabel(std::ostream &os, const std::string &lbl);
void StringToLower(std::string &str);
void Version(std::ostream &os = std::cout);