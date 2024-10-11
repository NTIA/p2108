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
#include <ctime>      // for localtime, time, time_t, strftime
#include <fstream>    // for ifstream, ofstream
#include <iomanip>    // for setw
#include <iostream>   // for cerr, cout
#include <string>     // for string, stoi, stod
#include <vector>     // for vector

/////////////////////////////
// Macros

// Make print-to-file statements more concise in driver
#define PRINT << std::endl << std::left << std::setw(25) <<
#define SETW13 << std::setw(13) <<

using namespace ITS::ITU::PSeries::P2108;

/////////////////////////////
// Functions

int ParseArguments(int argc, char **argv, DrvrParams &params);
void Help();
void Version();
int ValidateInputs(const DrvrParams &params);
int Validate_RequiredErrMsgHelper(const char *opt, int err);

// Reporting
void PrintClutterTypeLabel(std::ofstream &fp, const ClutterType clutter_type);
void PrintLabel(std::ofstream &fp, const char *lbl);

// Utils
int ParseInteger(const char *str, int &value);
int ParseDouble(const char *str, double &value);
int ParsingErrorHelper(int err, const char *msg);
std::string GetDatetimeString();