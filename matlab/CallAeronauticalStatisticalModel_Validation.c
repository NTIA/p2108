#include "mex.h"

const char *err_InvalidNumberOfInputs = ":InvalidNumberOfInputs";
const char *err_InvalidInputType = ":InvalidInputType";
const char *base_name = "MATLAB:P2108:";

const char* msg_start = "Value of '";
const char* msg_end = "' must be a number";

const char* input_vars[] = {"f__ghz", 
                            "theta__deg", 
                            "p"
                           };

CallAeronauticalStatisticalModel_Validation(int nrhs, 
                                            const mxArray *prhs[], 
                                            const char* fn_name){
    char *root_str, *full_id;
    root_str = mxCalloc(strlen(base_name) + strlen(fn_name) + 1, sizeof(char));

    strcat(root_str, base_name);
    strcat(root_str, fn_name);

    // validate input arguments
    if (nrhs != 3+1) { // +1 cause first array element is function name
        // build complete errID
        full_id = mxCalloc(strlen(root_str) + strlen(err_InvalidNumberOfInputs), sizeof(char));
        strcat(full_id, root_str);
        strcat(full_id, err_InvalidNumberOfInputs);

        mexErrMsgIdAndTxt(full_id, 
                          "Function takes 3 inputs.\n"
                          "AeronauticalStatisticalModel(double f__ghz, "
                          "double theta__deg, double p, double* L_ces__db)");
    }
    else
    {
        char *full_msg;

        // build complete errID
        full_id = mxCalloc(strlen(root_str) + strlen(err_InvalidInputType), sizeof(char));
        strcat(full_id, root_str);
        strcat(full_id, err_InvalidInputType);

        // loop through base area mode variables
        int baselen = sizeof(input_vars) / sizeof(input_vars[0]);
        for (int i = 0; i < baselen; i++)
        {
            if (!mxIsNumeric(prhs[i + 1])) {
                // build error msg
                full_msg = mxCalloc(strlen(msg_start) + strlen(input_vars[i]) + strlen(msg_end) + 1, sizeof(char));
                strcat(full_msg, msg_start);
                strcat(full_msg, input_vars[i]);
                strcat(full_msg, msg_end);

                // throw error
                mexErrMsgIdAndTxt(full_id, full_msg);
            }
        }
    }

    // no errors
    mxFree(root_str);
    mxFree(full_id);
}