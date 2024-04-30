#ifndef __ITS_ITU_PSERIES_P2108__
#define __ITS_ITU_PSERIES_P2108__

#include <cmath>  // For atan, fmin, log10, pow, sqrt, tan,
#define DLLEXPORT extern "C" __declspec(dllexport)

#define PI      3.1415926535897932384

// Bring some commonly-used mathematical functions into the global namespace
// This makes long equations a bit more readable while avoiding total namespace chaos.
using std::atan;
using std::fmin;
using std::log10;
using std::pow;
using std::sqrt;
using std::tan;

///////////////////////////////////////////////
// FUNCTIONS
//

// Public Functions
DLLEXPORT int AeronauticalStatisticalModel(double f__ghz, double theta__deg, 
    double p, double* L_ces__db);
DLLEXPORT int TerrestrialStatisticalModel(double f__ghz, double d__km, 
    double p, double* L_ctt__db);
DLLEXPORT int HeightGainTerminalCorrectionModel(double f__ghz, double h__meter,
    double w_s__meter, double R__meter, int clutter_type, double* A_h__db);

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

#endif