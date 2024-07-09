/** @file P2108.h
 * Interface header for this library
*/
#ifndef __ITS_ITU_PSERIES_P2108_P2108_H__
#define __ITS_ITU_PSERIES_P2108_P2108_H__

#include <cmath>  // For atan, fmin, log10, pow, sqrt, tan
#include "Enums.h"
#include "Errors.h"

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

// Define cross-platform EXPORTED
#ifndef DOXYGEN_SHOULD_SKIP
#   ifdef _WIN32
#       define EXPORTED extern "C" __declspec(dllexport)
#   else
#       define EXPORTED extern "C"
#   endif
#endif

// Bring some commonly-used mathematical functions into the global namespace
// This makes long equations a bit more readable while avoiding total namespace chaos.
using std::atan;
using std::fmin;
using std::log10;
using std::pow;
using std::sqrt;
using std::tan;

////////////////////////////////////////////////////////////////////////////////
// Constants
#define PI      3.14159265358979323846  /**< Approximate value of @f$ \pi @f$ */

////////////////////////////////////////////////////////////////////////////////
// Public Functions
EXPORTED int AeronauticalStatisticalModel(double f__ghz, double theta__deg, 
    double p, double* L_ces__db);
EXPORTED int TerrestrialStatisticalModel(double f__ghz, double d__km, 
    double p, double* L_ctt__db);
EXPORTED int HeightGainTerminalCorrectionModel(double f__ghz, double h__meter,
    double w_s__meter, double R__meter, ClutterType clutter_type, double* A_h__db);

////////////////////////////////////////////////////////////////////////////////
// Private Functions
double cot(double x);
double InverseComplementaryCumulativeDistribution(double q);
double Equation_2a(double nu);
double Equation_2b(double K_h2, double h__meter, double R__meter);
int Section3p1_InputValidation(double f__ghz, double h__meter, double w_s__meter,
    double R__meter);
int Section3p2_InputValidation(double f__ghz, double d__km, double p);
int Section3p3_InputValidation(double f__ghz, double theta__deg, double p);
double TerrestrialStatisticalModelHelper(double f__ghz, double d__km, double p);

} } } } // End namespace ITS::ITU::PSeries::P2108

#endif