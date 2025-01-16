/** @file ReturnCodes.cpp
 * Maps status message strings to driver return codes.
 */

#include "ReturnCodes.h"

#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

/*******************************************************************************
 * Get an error message string from a return code.
 * 
 * @param[in] code  Driver return code.
 * @return          A status message corresponding to the input code.
 ******************************************************************************/
std::string GetDrvrReturnStatusMsg(int code) {
    static const std::unordered_map<DrvrReturnCode, std::string> messages
        = {{DRVR__SUCCESS, "Successful execution"},
           {DRVR__RETURN_SUCCESS, "Internal driver success"},
           {DRVRERR__MISSING_OPTION, "No value provided for given argument"},
           {DRVRERR__INVALID_OPTION, "Unknown option specified"},
           {DRVRERR__OPENING_INPUT_FILE,
            "Failed to open the input file for reading"},
           {DRVRERR__OPENING_OUTPUT_FILE,
            "Failed to open the output file for writing"},
           {DRVRERR__PARSE, "Failed parsing inputs; unknown parameter"},
           {DRVRERR__PARSE_FREQ, "Failed to parse frequency value"},
           {DRVRERR__PARSE_THETA, "Failed to parse theta value"},
           {DRVRERR__PARSE_PERCENTAGE, "Failed to parse percentage value"},
           {DRVRERR__PARSE_HEIGHT, "Failed to parse antenna height value"},
           {DRVRERR__PARSE_STREET_WIDTH, "Failed to parse street width value"},
           {DRVRERR__PARSE_REPR_HEIGHT,
            "Failed to parse representative height value"},
           {DRVRERR__PARSE_CLUTTER_TYPE, "Failed to parse clutter type value"},
           {DRVRERR__PARSE_PATH_DIST, "Failed to parse path distance value"},
           {DRVRERR__VALIDATION_IN_FILE,
            "Option -i is required but was not provided"},
           {DRVRERR__VALIDATION_OUT_FILE,
            "Option -o is required but was not provided"},
           {DRVRERR__VALIDATION_MODEL,
            "Option -model is required but was not provided"}};

    // Construct status message
    std::string msg = DRIVER_NAME;
    msg += " v";
    msg += DRIVER_VERSION;
    if (code == DRVR__SUCCESS) {
        msg += " Status: ";
    } else {
        msg += " Error: ";
    }

    auto it = messages.find(static_cast<DrvrReturnCode>(code));
    if (it != messages.end()) {
        msg += it->second;
    } else {
        msg += "Undefined return code";
    }
    return msg;
}
