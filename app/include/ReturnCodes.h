/** @file ReturnCodes.h
 * Defines return codes for the driver
 */
#pragma once

#include <string>
#include <unordered_map>

/*******************************************************************************
 * Return Codes defined by this driver software.
 ******************************************************************************/
// clang-format off
enum DrvrReturnCode {
    // Primary Return Codes
    DRVR__SUCCESS = 1000,               /**< Successful execution */
    DRVR__RETURN_SUCCESS,               /**< Indicates driver should exit successfully */
    DRVRERR__MISSING_OPTION,            /**< No value provided for given argument */
    DRVRERR__INVALID_OPTION,            /**< Unknown option specified */
    DRVRERR__OPENING_INPUT_FILE,        /**< Failed to open the input file for reading */
    DRVRERR__OPENING_OUTPUT_FILE,       /**< Failed to open the output file for writing */

    // Input File Parsing Errors (1100-1199)
    DRVRERR__PARSE = 1100,              /**< Failed parsing inputs; unknown parameter */
    DRVRERR__PARSE_FREQ,                /**< Failed to parse frequency value */
    DRVRERR__PARSE_THETA,               /**< Failed to parse theta value */
    DRVRERR__PARSE_PERCENTAGE,          /**< Failed to parse percentage value */
    DRVRERR__PARSE_HEIGHT,              /**< Failed to parse antenna height value */
    DRVRERR__PARSE_STREET_WIDTH,        /**< Failed to parse street width value */
    DRVRERR__PARSE_REPR_HEIGHT,         /**< Failed to parse representative height value */
    DRVRERR__PARSE_CLUTTER_TYPE,        /**< Failed to parse clutter type value */
    DRVRERR__PARSE_PATH_DIST,           /**< Failed to parse path distance value */

    // Validation Errors (1200-1299)
    DRVRERR__VALIDATION_IN_FILE = 1200, /**< Input file not specified */
    DRVRERR__VALIDATION_OUT_FILE,       /**< Output file not specified */
    DRVRERR__VALIDATION_MODEL           /**< Model not specified */
};
// clang-format on

std::string GetDrvrReturnStatus(int code);
