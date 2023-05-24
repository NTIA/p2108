#include "mex.h"

// define external public function
extern int AeronauticalStatisticalModel(double f__ghz, double theta__deg, 
                                        double p, double* L_ces__db);

/*=========================================================================
 |
 |  Description:  Control the calling of the areonautical statistical
 |                clutter model
 |
 |        Input:  nrhs      - Number of input arguments
 |                prhs      - Array of pointers to input arguments
 |
 |       Output:  nlhs      - Number of output arguments
 |                plhs      - Array of pointers to output arguments
 |
 |      Returns:  [void]
 |
 *=======================================================================*/
void CallAeronauticalStatisticalModel(int nlhs, mxArray *plhs[], 
                                      int nrhs, const mxArray *prhs[])
{
    // validate inputs
    CallAeronauticalStatisticalModel_Validation(
        nrhs, 
        prhs,
        "MATLAB:P2108:CallAeronauticalStatisticalModel");

    // parse inputs
    double f__ghz = mxGetScalar(prhs[1]);
    double theta__deg = mxGetScalar(prhs[2]);
    double p = mxGetScalar(prhs[3]);

    // call external C library function
    double L_ces__db;
    int rtn = AeronauticalStatisticalModel(f__ghz, theta__deg, p, &L_ces__db);

    // record result
    plhs[0] = mxCreateDoubleScalar(rtn);
    plhs[1] = mxCreateDoubleScalar(L_ces__db);
}