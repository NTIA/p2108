/** @file Driver.h
 * Interface header for this driver executable
 */
#pragma once

#include "CommaSeparatedIterator.h"
#include "Errors.h"
#include "Structs.h"

// TODO-TEMPLATE: Include your library's main interface header
// #include "ITS.<YOUR_NAMESPACE>/<YOUR_LIBRARY>.h"

#include <ctime>     // for localtime_s, localtime_r, time, time_t, tm, strftime
#include <fstream>   // for std::ofstream
#include <iomanip>   // for std::setw
#include <iostream>  // for std::cerr, std::cout, std::ostream
#include <string>    // for std::string, std::stoi, std::stod
#include <tuple>     // for std::tie

/////////////////////////////
// Macros

// Make print-to-file statements more concise in driver
#define PRINT << std::endl << std::left << std::setw(25) <<
#define SETW13 << std::setw(13) <<

// TODO-TEMPLATE: use the namespace of your library
// using namespace ITS::YourLibraryNamespace::YourLibraryName;

/////////////////////////////
// Functions

int ParseArguments(int argc, char **argv, DrvrParams &params);
void Help(std::ostream &os = std::cout);
int ValidateInputs(const DrvrParams &params);


// Driver Utils
void Version(std::ostream &os = std::cout);
int Validate_RequiredErrMsgHelper(const std::string &opt, const int err);
int ParseInteger(const std::string &str, int &value);
int ParseDouble(const std::string &str, double &value);
int ParsingErrorHelper(const int err, const std::string &msg);
std::string GetDatetimeString();