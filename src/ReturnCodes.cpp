/** @file ReturnCodes.cpp
 * Maps status messages to library return codes
 */

#include "ITS.ITU.PSeries.P2108/P2108.h"

#ifdef _WIN32
    // Ensure strcpy_s is available on Windows
    #ifndef __STDC_LIB_EXT1__
        #define __STDC_LIB_EXT1__
    #endif
    #ifndef __STDC_WANT_LIB_EXT1__
        #define __STDC_WANT_LIB_EXT1__ 1
    #endif
#endif

#include <cstring>        // for strcpy_s
#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * Get an error message string from a return code.
 * 
 * @param[in] code  Integer return code.
 * @return          A status message corresponding to the input code.
 ******************************************************************************/
std::string GetReturnStatus(const int code) {
    static const std::unordered_map<ReturnCode, std::string> messages
        = {{SUCCESS, "Successful execution"},
           {ERROR31__FREQUENCY, "Frequency must be between 0.3 and 3 GHz"},
           {ERROR31__ANTENNA_HEIGHT, "Antenna height must be >= 0 meters"},
           {ERROR31__STREET_WIDTH, "Street width must be > 0 meters"},
           {ERROR31__CLUTTER_HEIGHT,
            "Representative clutter height must be > 0 meters"},
           {ERROR31__CLUTTER_TYPE, "Invalid value for clutter type"},
           {ERROR32__FREQUENCY, "Frequency must be between 2 and 67 GHz"},
           {ERROR32__DISTANCE, "Path distance must be >= 0.25 km"},
           {ERROR32__PERCENTAGE, "Percentage must be between 0 and 100"},
           {ERROR33__FREQUENCY, "Frequency must be between 10 and 100 GHz"},
           {ERROR33__THETA, "Elevation angle must be between 0 and 100 GHz"},
           {ERROR33__PERCENTAGE, "Percentage must be between 0 and 100"}};
    // Construct status message
    std::string msg = LIBRARY_NAME;
    if (code == SUCCESS) {
        msg += " Status: ";
    } else {
        msg += " Error: ";
    }

    auto it = messages.find(static_cast<ReturnCode>(code));
    if (it != messages.end()) {
        msg += it->second;
    } else {
        msg += "Undefined return code";
    }
    return msg;
}

/*******************************************************************************
 * Get an error message string (as C-style string) from a return code.
 * 
 * @param[in] code  Integer return code.
 * @return          A status message corresponding to the input code.
 ******************************************************************************/
EXPORTED char *GetReturnStatusCharArray(const int code) {
    const std::string msg = GetReturnStatus(code);
    char *c_msg = new char[msg.size() + 1];
#ifdef _WIN32
    strcpy_s(c_msg, msg.size() + 1, msg.c_str());
#else
    strcpy(c_msg, msg.c_str());
#endif
    return c_msg;
}

/*******************************************************************************
 * Free the memory allocated by GetReturnStatusCharArray
 * 
 * @param[in] c_msg  The status message C-style string to delete
 ******************************************************************************/
EXPORTED void FreeReturnStatusCharArray(char *c_msg) {
    delete[] c_msg;
}

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS