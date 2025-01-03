/** @file TestUtils.h
 * Primary header for fixtures or common functions used by unit tests.
 */
#pragma once

// clang-format off
// GoogleTest must be included first
#include <gtest/gtest.h>  // GoogleTest
// clang-format on

#include "P2108.h"

#include <string>  // for std::string
#include <vector>  // for std::vector

using namespace ITS::ITU::PSeries::P2108;

// Absolute tolerance for checking model outputs against test data
constexpr double ABSTOL__DB = 0.1;

void AppendDirectorySep(std::string &str);
std::string GetDataDirectory();

struct AeronauticalStatisticalModelTestData {
        double f__ghz;
        double theta__deg;
        double p;
        ReturnCode rtn;
        double L_ces__db;
};

struct HeightGainTerminalCorrectionModelTestData {
        double f__ghz;
        double h__meter;
        double w_s__meter;
        double R__meter;
        ClutterType clutter_type;
        ReturnCode rtn;
        double A_h__db;
};

struct TerrestrialStatisticalModelTestData {
        double f__ghz;
        double d__km;
        double p;
        ReturnCode rtn;
        double L_ctt__db;
};

std::vector<AeronauticalStatisticalModelTestData>
    readAeronauticalStatisticalModelTestData(const std::string &filename);

std::vector<HeightGainTerminalCorrectionModelTestData>
    readHeightGainTerminalCorrectionModelTestData(const std::string &filename);

std::vector<TerrestrialStatisticalModelTestData>
    readTerrestrialStatisticalModelTestData(const std::string &filename);
