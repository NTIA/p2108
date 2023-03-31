#include "mex.h"

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

    /* Verify the first input argument is a string and a row vector */
    if (mxIsChar(prhs[0]) != 1)
      mexErrMsgIdAndTxt( "MATLAB:P2108:inputNotString", "First input must be function name (string).");
    if (mxGetM(prhs[0])!=1)
      mexErrMsgIdAndTxt( "MATLAB:P2108:inputNotVector", "First input must be a row vector.");
    
    /* get the length of the input string */
    buflen = (mxGetM(prhs[0]) * mxGetN(prhs[0])) + 1;

    /* allocate memory for output string */
    output_buf=mxCalloc(buflen, sizeof(char));

    /* copy the string data from prhs[0] into a C string input_ buf.    */
    input_buf = mxArrayToString(prhs[0]);

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
    
        // TODO: Error: Unknown Function
    }

    
    mxFree(input_buf);
    return;
}

