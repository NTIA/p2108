/** @file P2108.h
 * Interface header for this library
 */
#pragma once

#include "Enums.h"
#include "ReturnCodes.h"

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

// Define cross-platform EXPORTED
#ifndef DOXYGEN_SHOULD_SKIP
    #ifdef _WIN32
        #define EXPORTED extern "C" __declspec(dllexport)
    #else
        #define EXPORTED extern "C"
    #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Constants
/** Approximate value of @f$ \pi @f$ */
constexpr double PI = 3.14159265358979323846;

////////////////////////////////////////////////////////////////////////////////
// Public Functions
EXPORTED ReturnCode AeronauticalStatisticalModel(
    const double f__ghz,
    const double theta__deg,
    const double p,
    double &L_ces__db
);
EXPORTED ReturnCode TerrestrialStatisticalModel(
    const double f__ghz, const double d__km, const double p, double &L_ctt__db
);
EXPORTED ReturnCode HeightGainTerminalCorrectionModel(
    const double f__ghz,
    const double h__meter,
    const double w_s__meter,
    const double R__meter,
    const ClutterType clutter_type,
    double &A_h__db
);

////////////////////////////////////////////////////////////////////////////////
// Private Functions
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
