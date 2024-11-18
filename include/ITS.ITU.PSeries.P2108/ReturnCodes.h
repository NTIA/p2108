/** @file ReturnCodes.h
 * Contains return codes used by this software
 */
#pragma once

#include <string>         // for std::string
#include <unordered_map>  // for std::unordered_map

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * Return Codes defined by this software (0-127)
 ******************************************************************************/
// clang-format off
enum ReturnCode {
    SUCCESS = 0,               /**< Successful execution */

    // Section 3.1 Error Codes
    ERROR31__FREQUENCY = 32,   /**< Frequency must be between 0.3 and 3 GHz */
    ERROR31__ANTENNA_HEIGHT,   /**< Antenna height must be @f$ \geq @f$ 0 meters */
    ERROR31__STREET_WIDTH,     /**< Street width must be @f$ > @f$ 0 meters */
    ERROR31__CLUTTER_HEIGHT,   /**< Representative clutter height must be @f$ > @f$ 0 meters */
    ERROR31__CLUTTER_TYPE,     /**< Invalid value for clutter type */

    // Section 3.2 Error Codes
    ERROR32__FREQUENCY = 48,   /**< Frequency must be between 2 and 67 GHz */
    ERROR32__DISTANCE,         /**< Path distance must be @f$ \geq @f$ 0.25 km */
    ERROR32__PERCENTAGE,       /**< Percentage must be between 0 and 100 */

    // Section 3.3 Error Codes
    ERROR33__FREQUENCY = 64,   /**< Frequency must be between 10 and 100 GHz */
    ERROR33__THETA,            /**< Elevation angle must be between 0 and 100 GHz */
    ERROR33__PERCENTAGE,       /**< Percentage must be between 0 and 100 */
};
// clang-format on

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS
