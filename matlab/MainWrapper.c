#include "mex.h"

/*=========================================================================
 |
 |  Description:  Main entry function for MATLAB
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
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    char *input_buf, *output_buf;
    size_t buflen;
    
    /* check for proper number of arguments */
    /*if(nrhs!=1) 
      mexErrMsgIdAndTxt( "MATLAB:revord:invalidNumInputs",
              "One input required.");
    else if(nlhs > 1) 
      mexErrMsgIdAndTxt( "MATLAB:revord:maxlhs",
              "Too many output arguments.");*/

    // verify the first input argument is a string and a row vector
    if (mxIsChar(prhs[0]) != 1)
      mexErrMsgIdAndTxt("MATLAB:P2108:InputNotString", "First input must be function name (string).");
    if (mxGetM(prhs[0]) != 1)
      mexErrMsgIdAndTxt("MATLAB:P2108:InputNotVector", "First input must be a row vector.");
    
    // get the length of the input string
    buflen = (mxGetM(prhs[0]) * mxGetN(prhs[0])) + 1;

    // allocate memory for output string
    output_buf = mxCalloc(buflen, sizeof(char));

    // copy the string data from prhs[0] into a C string input_buf
    input_buf = mxArrayToString(prhs[0]);

    // decide action being requested by the caller
    if (strcmp("AeronauticalStatisticalModel", input_buf) == 0) {
        CallAeronauticalStatisticalModel(nlhs, plhs, nrhs, prhs);
    }
    else if (strcmp("HeightGainTerminalCorrectionModel", input_buf) == 0) {
        CallHeightGainTerminalCorrectionModel(nlhs, plhs, nrhs, prhs);
    }
    else if (strcmp("TerrestrialStatisticalModel", input_buf) == 0) {
        CallTerrestrialStatisticalModel(nlhs, plhs, nrhs, prhs);
    }
    else if (strcmp("Version", input_buf) == 0 ||
             strcmp("Info", input_buf) == 0) {
        
        mexPrintf("Recommendation ITU-R P.2108-1: Prediction of clutter loss\n");
        
        mexPrintf("Version 1.0.0\n");
    }
    else {
        mexErrMsgIdAndTxt("MATLAB:P2108:UnKnownFunction", "Unknown function name.");
    }

    mxFree(input_buf);
    return;
}