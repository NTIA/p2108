/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#pragma once

#include <string>  // For std::string

/////////////////////////////
// Enums
/** Valid values of "model" command line option */
enum class P2108Model {
    NOT_SET = -1, /**< Invalid model selection */
    HGTCM = 1,    /**< Height Gain Terminal Correction Model */
    TSM = 2,      /**< Terrestrial Statistical Model */
    ASM = 3,      /**< Aeronautical Statistical Model */
};

/////////////////////////////
// Data Structures

/** Parameters provided to the command line driver */
struct DrvrParams {
        std::string in_file = "";               /**< Input file */
        std::string out_file = "";              /**< Output file */
        P2108Model model = P2108Model::NOT_SET; /**< Model selection */
};

/** Input parameters for the Height Gain Terminal Correction Model */
struct HGTCParams {
        double f__ghz;     /**< Frequency, in GHz */
        double h__meter;   /**< Antenna height, in meters */
        double w_s__meter; /**< Street width, in meters */
        double R__meter;   /**< Representative clutter height, in meters */
        ITS::ITU::PSeries::P2108::ClutterType
            clutter_type; /**< Clutter type (enum value) */
};

/** Input parameters for the Terrestrial Statistical Model */
struct TSMParams {
        double f__ghz; /**< Frequency, in GHz */
        double d__km;  /**< Path distance, in km */
        double p;      /**< Percentage of locations */
};

/** Input parameters for the Aeronautical Statistical Model */
struct ASMParams {
        double f__ghz;     /**< Frequency, in GHz */
        double theta__deg; /**< Elevation angle, in degrees */
        double p;          /**< Percentage of locations */
};