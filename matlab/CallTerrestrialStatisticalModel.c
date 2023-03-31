#include "mex.h"

// define external public function
extern int TerrestrialStatisticalModel(double f__ghz, double d__km, 
    double p, double* L_ctt__db);

void CallTerrestrialStatisticalModel(int nlhs, mxArray *plhs[], int nrhs, 
    const mxArray *prhs[]) {

    // validate inputs
    CallTerrestrialStatisticalModel_Validation(
        nrhs, 
        prhs,
        "MATLAB:P2108:CallTerrestrialStatisticalModel");

    // parse inputs
    double f__ghz = mxGetScalar(prhs[1]);
    double d__km = mxGetScalar(prhs[2]);
    double p = mxGetScalar(prhs[3]);

    // call external C library function
    double L_ctt__db;
    int rtn = TerrestrialStatisticalModel(f__ghz, d__km, p, &L_ctt__db);

    // record result
    plhs[0] = mxCreateDoubleScalar(rtn);
    plhs[1] = mxCreateDoubleScalar(L_ctt__db);
}