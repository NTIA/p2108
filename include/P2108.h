#include "math.h"

#define DLLEXPORT extern "C" __declspec(dllexport)

#define PI      3.1415926535897932384

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
