/** @file P2108.h
 * Interface header for this library
 */
#pragma once

#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

// Define cross-platform PROPLIB_API to export functions
#ifndef DOXYGEN_SHOULD_SKIP
    #ifndef PROPLIB_API
        #ifdef _WIN32
            #define PROPLIB_API extern "C" __declspec(dllexport)
        #else
            #define PROPLIB_API extern "C"
        #endif
    #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Enums

/** Clutter type enum, based on Table 3 in Section 3.1 */
enum ClutterType {
    WATER_SEA = 1,    /**< Water/sea clutter type */
    OPEN_RURAL = 2,   /**< Open/rural clutter type */
    SUBURBAN = 3,     /**< Suburban clutter type */
    URBAN = 4,        /**< Urban clutter type */
    TREES_FOREST = 5, /**< Trees/forest clutter type */
    DENSE_URBAN = 6,  /**< Dense urban clutter type */
};

/*******************************************************************************
 * Default values of the representative clutter height @f$ R @f$,
 * in meters, by clutter type.
 *
 * These should be used as inputs to the height gain terminal
 * correction model when local information is not available.
 ******************************************************************************/
enum RepresentativeClutterHeight {
    R__WATER_SEA = 10,    /**< @f$ R @f$ for the trees/forest clutter type */
    R__OPEN_RURAL = 10,   /**< @f$ R @f$ for the open/rural clutter type */
    R__SUBURBAN = 10,     /**< @f$ R @f$ for the suburban clutter type */
    R__URBAN = 15,        /**< @f$ R @f$ for the urban clutter type */
    R__TREES_FOREST = 15, /**< @f$ R @f$ for the trees/forest clutter type */
    R__DENSE_URBAN = 20,  /**< @f$ R @f$ for the dense urban clutter type */
};

/*******************************************************************************
 * Return Codes defined by this software (0-127)
 ******************************************************************************/
// clang-format off
enum ReturnCode {
    SUCCESS = 0,               /**< Successful execution */

    // Section 3.1 Error Codes
    ERROR31__FREQUENCY = 32,   /**< Frequency must be between 0.3 and 3 GHz */
    ERROR31__ANTENNA_HEIGHT,   /**< Antenna height must be @f$ \geq @f$ 0 meters */
    ERROR31__STREET_WIDTH,     /**< Street width must be @f$ > @f$ 0 meters */
    ERROR31__CLUTTER_HEIGHT,   /**< Representative clutter height must be @f$ > @f$ 0 meters */
    ERROR31__CLUTTER_TYPE,     /**< Invalid value for clutter type */

    // Section 3.2 Error Codes
    ERROR32__FREQUENCY = 48,   /**< Frequency must be between 2 and 67 GHz */
    ERROR32__DISTANCE,         /**< Path distance must be @f$ \geq @f$ 0.25 km */
    ERROR32__PERCENTAGE,       /**< Percentage must be between 0 and 100 */

    // Section 3.3 Error Codes
    ERROR33__FREQUENCY = 64,   /**< Frequency must be between 10 and 100 GHz */
    ERROR33__THETA,            /**< Elevation angle must be between 0 and 100 GHz */
    ERROR33__PERCENTAGE,       /**< Percentage must be between 0 and 100 */
};
// clang-format on

////////////////////////////////////////////////////////////////////////////////
// Constants
/** Approximate value of @f$ \pi @f$ */
constexpr double PI = 3.14159265358979323846;

////////////////////////////////////////////////////////////////////////////////
// Public Functions
PROPLIB_API ReturnCode AeronauticalStatisticalModel(
    const double f__ghz,
    const double theta__deg,
    const double p,
    double &L_ces__db
);
PROPLIB_API ReturnCode TerrestrialStatisticalModel(
    const double f__ghz, const double d__km, const double p, double &L_ctt__db
);
PROPLIB_API ReturnCode HeightGainTerminalCorrectionModel(
    const double f__ghz,
    const double h__meter,
    const double w_s__meter,
    const double R__meter,
    const ClutterType clutter_type,
    double &A_h__db
);
PROPLIB_API char *GetReturnStatusCharArray(const int code);
PROPLIB_API void FreeReturnStatusCharArray(char *c_msg);

////////////////////////////////////////////////////////////////////////////////
// Private Functions
std::string GetReturnStatus(const int code);
double cot(const double x);
double InverseComplementaryCumulativeDistribution(const double q);
double Equation_2a(const double nu);
double Equation_2b(
    const double K_h2, const double h__meter, const double R__meter
);
ReturnCode Section3p1_InputValidation(
    const double f__ghz,
    const double h__meter,
    const double w_s__meter,
    const double R__meter
);
ReturnCode Section3p2_InputValidation(
    const double f__ghz, const double d__km, const double p
);
ReturnCode Section3p3_InputValidation(
    const double f__ghz, const double theta__deg, const double p
);
double TerrestrialStatisticalModelHelper(
    const double f__ghz, const double d__km, const double p
);


}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS
