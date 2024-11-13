/** @file ReturnCodes.h
 * Defines return codes for the driver
 */
#pragma once

#include <string>  // for std::string

/*******************************************************************************
 * Return Codes defined by this driver software (128-255)
 ******************************************************************************/
// clang-format off
enum DrvrReturnCode {
    // Primary Return Codes
    DRVR__SUCCESS = 128,                /**< Successful execution */
    DRVR__RETURN_SUCCESS,               /**< Indicates driver should exit successfully */
    DRVRERR__MISSING_OPTION,            /**< No value provided for given argument */
    DRVRERR__INVALID_OPTION,            /**< Unknown option specified */
    DRVRERR__OPENING_INPUT_FILE,        /**< Failed to open the input file for reading */
    DRVRERR__OPENING_OUTPUT_FILE,       /**< Failed to open the output file for writing */

    // Input File Parsing Errors
    DRVRERR__PARSE = 160,               /**< Failed parsing inputs; unknown parameter */
    DRVRERR__PARSE_FREQ,                /**< Failed to parse frequency value */
    DRVRERR__PARSE_THETA,               /**< Failed to parse theta value */
    DRVRERR__PARSE_PERCENTAGE,          /**< Failed to parse percentage value */
    DRVRERR__PARSE_HEIGHT,              /**< Failed to parse antenna height value */
    DRVRERR__PARSE_STREET_WIDTH,        /**< Failed to parse street width value */
    DRVRERR__PARSE_REPR_HEIGHT,         /**< Failed to parse representative height value */
    DRVRERR__PARSE_CLUTTER_TYPE,        /**< Failed to parse clutter type value */
    DRVRERR__PARSE_PATH_DIST,           /**< Failed to parse path distance value */

    // Validation Errors
    DRVRERR__VALIDATION_IN_FILE = 192,  /**< Input file not specified */
    DRVRERR__VALIDATION_OUT_FILE,       /**< Output file not specified */
    DRVRERR__VALIDATION_MODEL,          /**< Model not specified */
};
// clang-format on

std::string GetDrvrReturnStatusMsg(int code);
