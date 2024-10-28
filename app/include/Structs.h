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
struct HGTCMParams {
        double f__ghz;     /**< Frequency, in GHz */
        double h__meter;   /**< Antenna height, in meters */
        double w_s__meter; /**< Street width, in meters */
        double R__meter;   /**< Representative clutter height, in meters */
        ClutterType clutter_type; /**< Clutter type (enum value) */
};

/** Key names for Height Gain Terminal Correction Model input file parameters */
struct HGTCMInputKeys {
        static const std::string f__ghz;     /**< Frequency, in GHz */
        static const std::string h__meter;   /**< Antenna height, in meters */
        static const std::string w_s__meter; /**< Street width, in meters */
        static const std::string
            R__meter; /**< Representative clutter height, in meters */
        static const std::string clutter_type; /**< Clutter type (enum value) */
};
const std::string HGTCMInputKeys::f__ghz = "f__ghz";
const std::string HGTCMInputKeys::h__meter = "h__meter";
const std::string HGTCMInputKeys::w_s__meter = "w_s__meter";
const std::string HGTCMInputKeys::R__meter = "r__meter";
const std::string HGTCMInputKeys::clutter_type = "clutter_type";

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
};
const std::string TSMInputKeys::f__ghz = "f__ghz";
const std::string TSMInputKeys::d__km = "d__km";
const std::string TSMInputKeys::p = "p";

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
};
const std::string ASMInputKeys::f__ghz = "f__ghz";
const std::string ASMInputKeys::theta__deg = "theta__deg";
const std::string ASMInputKeys::p = "p";