/** @file Errors.h
 * Defines return codes for the driver
 */
#pragma once

// clang-format off

// Define "SUCCESS" macro if not imported already
#ifndef SUCCESS
#define SUCCESS 0 /**< Successful execution */
#endif

/** Primary Return Codes (1000-1099) */
#define DRVR__RETURN_SUCCESS                1000  /**< Internal driver success code */
#define DRVRERR__MISSING_OPTION             1001  /**< No value provided for given argument */
#define DRVRERR__INVALID_OPTION             1002  /**< Unknown option specified */
#define DRVRERR__OPENING_INPUT_FILE         1003  /**< Failed to open the input file for reading */
#define DRVRERR__OPENING_OUTPUT_FILE        1004  /**< Failed to open the output file for writing */

/** Input File Parsing Errors (1100-1199) */
#define DRVRERR__PARSE                      1100  /**< General error parsing inputs */
#define DRVRERR__PARSE_FREQ                 1101  /**< Error parsing frequency value */
#define DRVRERR__PARSE_THETA                1102  /**< Error parsing theta value */
#define DRVRERR__PARSE_PERCENTAGE           1103  /**< Error parsing percentage value */
#define DRVRERR__PARSE_HEIGHT               1104  /**< Error parsing antenna height value */
#define DRVRERR__PARSE_STREET_WIDTH         1105  /**< Error parsing street width value */
#define DRVRERR__PARSE_REPR_HEIGHT          1106  /**< Error parsing representative height value */
#define DRVRERR__PARSE_CLUTTER_TYPE         1107  /**< Error parsing clutter type value */
#define DRVRERR__PARSE_PATH_DIST            1108  /**< Error parsing path distance value */

/** Validation Errors (1200-1299) */
#define DRVRERR__VALIDATION_IN_FILE         1200  /**< Input file not specified */
#define DRVRERR__VALIDATION_OUT_FILE        1201  /**< Output file not specified */
#define DRVRERR__VALIDATION_MODEL           1202  /**< Model not specified */

// clang-format on