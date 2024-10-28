/** @file Errors.h
 * Contains return codes used by this software
 */
#ifndef __ITS_ITU_PSERIES_P2108_ERRORS__
#define __ITS_ITU_PSERIES_P2108_ERRORS__

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

///////////////////////////////////////////////
// RETURN CODES

// clang-format off

#define SUCCESS                        0  /**< Successful execution */

// Section 3.1 Error Codes
#define ERROR31__FREQUENCY          3100  /**< Frequency must be between 0.3 and 3 GHz, inclusive */
#define ERROR31__ANTENNA_HEIGHT     3101  /**< Antenna height must be @f$ \geq @f$ 0 meters */
#define ERROR31__STREET_WIDTH       3102  /**< Street width must be @f$ > @f$ 0 meters */
#define ERROR31__CLUTTER_HEIGHT     3103  /**< Representative clutter height must be @f$ > @f$ 0 meters */
#define ERROR31__CLUTTER_TYPE       3104  /**< Invalid value for clutter type */

// Section 3.2 Error Codes
#define ERROR32__FREQUENCY          3200  /**< Frequency must be between 2 and 67 GHz, inclusive */
#define ERROR32__DISTANCE           3201  /**< Path distance must be @f$ \geq @f$ 0.25 km */
#define ERROR32__PERCENTAGE         3202  /**< Percentage must be between 0 and 100 */

// Section 3.3 Error Codes
#define ERROR33__FREQUENCY          3300  /**< Frequency must be between 10 and 100 GHz, inclusive */
#define ERROR33__THETA              3301  /**< Elevation angle must be between 0 and 100 GHz, inclusive */
#define ERROR33__PERCENTAGE         3302  /**< Percentage must be between 0 and 100, inclusive */

// clang-format on

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS

#endif
