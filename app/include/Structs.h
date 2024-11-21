/** @file Structs.h
 * Contains data structures and type macros used by this software
*/
#pragma once

#include "P2108.h"  // For ClutterType enum

#include <string>  // for std::string

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
struct HGTCMParams {
        double f__ghz;     /**< Frequency, in GHz */
        double h__meter;   /**< Antenna height, in meters */
        double w_s__meter; /**< Street width, in meters */
        double R__meter;   /**< Representative clutter height, in meters */
        ITS::ITU::PSeries::P2108::ClutterType
            clutter_type; /**< Clutter type (enum value) */
};

/** Key names for Height Gain Terminal Correction Model input file parameters */
struct HGTCMInputKeys {
        static const std::string f__ghz;     /**< Frequency, in GHz */
        static const std::string h__meter;   /**< Antenna height, in meters */
        static const std::string w_s__meter; /**< Street width, in meters */
        static const std::string
            R__meter; /**< Representative clutter height, in meters */
        static const std::string clutter_type; /**< Clutter type (enum value) */
};  // Constants defined in app/src/HeightGainTerminalCorrectionModel.cpp

/** Input parameters for the Terrestrial Statistical Model */
struct TSMParams {
        double f__ghz; /**< Frequency, in GHz */
        double d__km;  /**< Path distance, in km */
        double p;      /**< Percentage of locations */
};

/** Key names for Terrestrial Statistical Model input file parameters */
struct TSMInputKeys {
        static const std::string f__ghz; /**< Frequency, in GHz */
        static const std::string d__km;  /**< Path distance, in km */
        static const std::string p;      /**< Percentage of locations */
};  // Constants defined in app/src/TerrestrialStatisticalModel.cpp

/** Input parameters for the Aeronautical Statistical Model */
struct ASMParams {
        double f__ghz;     /**< Frequency, in GHz */
        double theta__deg; /**< Elevation angle, in degrees */
        double p;          /**< Percentage of locations */
};

/** Key names for Aeronautical Statistical Model input file parameters */
struct ASMInputKeys {
        static const std::string f__ghz;     /**< Frequency, in GHz */
        static const std::string theta__deg; /**< Elevation angle, in degrees */
        static const std::string p;          /**< Percentage of locations */
};  // Constants defined in app/src/AeronauticalStatisticalModel.cpp