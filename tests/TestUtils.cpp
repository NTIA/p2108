#include "TestUtils.h"

#include <fstream>
#include <sstream>

void appendDirectorySep(std::string &str) {
#ifdef _WIN32
    str += "\\";
#else
    str += "/";
#endif
}

std::string getDataDirectory() {
    std::string dataDir(__FILE__);
    dataDir.resize(dataDir.find_last_of("/\\"));
    appendDirectorySep(dataDir);
    dataDir += "data";
    appendDirectorySep(dataDir);
    return dataDir;
}

std::vector<AeronauticalStatisticalModelTestData>
    readAeronauticalStatisticalModelTestData(const std::string &filename) {
    std::vector<AeronauticalStatisticalModelTestData> testData;
    std::string dataDir = getDataDirectory();
    std::ifstream file(dataDir + filename);
    std::string line;
    // struct to store data from a single line of CSV:
    AeronauticalStatisticalModelTestData d;
    char c;  // single-character representing the comma (delimiter)
    int rtn_value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> d.f__ghz >> c >> d.theta__deg >> c >> d.p >> c >> rtn_value
            >> c >> d.L_ces__db) {
            d.rtn = static_cast<ReturnCode>(rtn_value);
            testData.push_back(d);
        }
    }
    return testData;
}

std::vector<HeightGainTerminalCorrectionModelTestData>
    readHeightGainTerminalCorrectionModelTestData(const std::string &filename) {
    std::vector<HeightGainTerminalCorrectionModelTestData> testData;
    std::string dataDir = getDataDirectory();
    std::ifstream file(dataDir + filename);
    std::string line;
    // struct to store data from a single line of CSV:
    HeightGainTerminalCorrectionModelTestData d;
    char c;  // single-character representing the comma (delimiter)
    int clutter_type_value;
    int rtn_value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> d.f__ghz >> c >> d.h__meter >> c >> d.w_s__meter >> c
            >> d.R__meter >> c >> clutter_type_value >> c >> rtn_value >> c
            >> d.A_h__db) {
            // Convert integers to enum
            d.clutter_type = static_cast<ClutterType>(clutter_type_value);
            d.rtn = static_cast<ReturnCode>(rtn_value);
            testData.push_back(d);
        }
    }
    return testData;
}

std::vector<TerrestrialStatisticalModelTestData>
    readTerrestrialStatisticalModelTestData(const std::string &filename) {
    std::vector<TerrestrialStatisticalModelTestData> testData;
    std::string dataDir = getDataDirectory();
    std::ifstream file(dataDir + filename);
    std::string line;
    // struct to store data from a single line of CSV:
    TerrestrialStatisticalModelTestData d;
    char c;  // single-character representing the comma (delimiter)
    int rtn_value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> d.f__ghz >> c >> d.d__km >> c >> d.p >> c >> rtn_value >> c
            >> d.L_ctt__db) {
            d.rtn = static_cast<ReturnCode>(rtn_value);
            testData.push_back(d);
        }
    }
    return testData;
}
