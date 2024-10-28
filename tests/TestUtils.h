#pragma once

#include "ITS.ITU.PSeries.P2108/P2108.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace ITS::ITU::PSeries::P2108;

// Absolute tolerance for checking model outputs against test data
#define ABSTOL__DB 0.1

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
