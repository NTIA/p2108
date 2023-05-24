#include "mex.h"

/*=========================================================================
 |
 |  Description:  Validate number and type of inputs for height gain
 |                terminal correction model
 |
 |        Input:  nrhs      - Number of input arguments
 |                prhs      - Array of pointers to input arguments
 |                fn_name   - Function name
 |
 |       Output:  [void]
 |
 |      Returns:  [void]
 |
 *=======================================================================*/
CallHeightGainTerminalCorrectionModel_Validation(int nrhs, 
                                                 const mxArray *prhs[], 
                                                 const char* fn_name)
{
    char* err_InvalidNumberOfInputs = ":InvalidNumberOfInputs";
    char* err_InvalidInputType = ":InvalidInputType";
    char* base_name = "MATLAB:P2108:";

    char* msg_start = "Value of '";
    char* msg_end = "' must be a number";

    char* input_vars[] = {"f__ghz", 
                          "h__meter", 
                          "w_s__meter",
                          "R__meter",
                          "clutter_type"
                         };

    char* root_str;
    char* full_id;
    root_str = mxCalloc(strlen(base_name) + strlen(fn_name) + 1, sizeof(char));

    strcat(root_str, base_name);
    strcat(root_str, fn_name);

    // validate input arguments
    if (nrhs != 5 + 1)  // +1 cause first array element is function name
    {
        // build complete errID
        full_id = mxCalloc(strlen(root_str) + strlen(err_InvalidNumberOfInputs), sizeof(char));
        strcat(full_id, root_str);
        strcat(full_id, err_InvalidNumberOfInputs);
 
        mexErrMsgIdAndTxt(full_id, 
            "Function takes 5 inputs.\n"
            "HeightGainTerminalCorrectionModel(double f__ghz, "
            "double h__meter, double w_s__meter, double R__meter, "
            "int clutter_type, double *A_h__db)");
    }
    else
    {
        char* full_msg;

        // build complete errID
        full_id = mxCalloc(strlen(root_str) + strlen(err_InvalidInputType), sizeof(char));
        strcat(full_id, root_str);
        strcat(full_id, err_InvalidInputType);

        // loop through variables
        int baselen = sizeof(input_vars) / sizeof(input_vars[0]);
        for (int i = 0; i < baselen; i++)
        {
            // check variable type
            if (!mxIsNumeric(prhs[i + 1])) 
            {
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