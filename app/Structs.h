/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#pragma once

#include <string>  // For std::string

/////////////////////////////
// Enums
enum class P2108Model {
    NOT_SET = -1,
    HGTCM = 1,
    TSM = 2,
    ASM = 3,
};

/////////////////////////////
// Data Structures

struct DrvrParams {
        std::string in_file = "";   // Input file
        std::string out_file = "";  // Output file
        P2108Model model = P2108Model::NOT_SET;
};

struct ASMParams {
        double f__ghz;
        double theta__deg;
        double p;
};

struct HGTCParams {
        double f__ghz;
        double h__meter;
        double w_s__meter;
        double R__meter;
        ITS::ITU::PSeries::P2108::ClutterType clutter_type;
};

struct TSMParams {
        double f__ghz;
        double d__km;
        double p;
};