#include "mex.h"

// define external public function
extern int HeightGainTerminalCorrectionModel(double f__ghz, double h__meter, 
    double w_s__meter, double R__meter, int clutter_type, double *A_h__db);

/*=========================================================================
 |
 |  Description:  Control the calling of the height gain terminal 
 |                correction clutter model
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
void CallHeightGainTerminalCorrectionModel(int nlhs, mxArray *plhs[], 
                                           int nrhs, const mxArray *prhs[])
{
    // validate inputs
    CallHeightGainTerminalCorrectionModel_Validation(
        nrhs, 
        prhs,
        "MATLAB:P2108:CallHeightGainTerminalCorrectionModel");

    // parse inputs
    double f__ghz = mxGetScalar(prhs[1]);
    double h__meter = mxGetScalar(prhs[2]);
    double w_s__meter = mxGetScalar(prhs[3]);
    double R__meter = mxGetScalar(prhs[4]);
    int clutter_type = (int)mxGetScalar(prhs[5]);

    // call external C library function
    double A_h__db;
    int rtn = HeightGainTerminalCorrectionModel(f__ghz, h__meter, 
        w_s__meter, R__meter, clutter_type, &A_h__db);

    // record result
    plhs[0] = mxCreateDoubleScalar(rtn);
    plhs[1] = mxCreateDoubleScalar(A_h__db);
}