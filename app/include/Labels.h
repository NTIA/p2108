/** @file Labels.h
 * Defines text labels for errors, warnings, and enums
 */
#pragma once

// clang-format off

// Skip Doxygen generation for labels
#ifndef DOXYGEN_SHOULD_SKIP

/** Labels */
#define LBL__SUCCESS                       "Success - No Errors"
#define LBL__SUCCESS_WITH_WARNINGS         "Success - but with warnings"
#define LBL__NO_WARNINGS                   "No Warnings"

/** P.2108 Model Names */
#define LBL__HGTCM                         "Height Gain Terminal Correction Model"
#define LBL__TSM                           "Terrestrial Statistical Model"
#define LBL__ASM                           "Aeronautical Statistical Model"

/** Height Gain Terminal Correction Clutter Types */
#define LBL__CLUTTERTYPE_WATER_SEA         "Water/sea clutter type"
#define LBL__CLUTTERTYPE_OPEN_RURAL        "Open/rural clutter type"
#define LBL__CLUTTERTYPE_SUBURBAN          "Suburban clutter type"
#define LBL__CLUTTERTYPE_URBAN             "Urban clutter type"
#define LBL__CLUTTERTYPE_TREES_FOREST      "Trees/forest clutter type"
#define LBL__CLUTTERTYPE_DENSE_URBAN       "Dense urban clutter type"

/** Error Definitions */
#define LBL__ERROR_INVALID_VALUE           "Invalid Value"
#define LBL__ERROR_UNKNOWN                 "An unknown error occurred"
#define LBL__ERROR31_FREQUENCY             "Frequency must be between 0.3 and 3 GHz, inclusive"
#define LBL__ERROR31_ANTENNA_HEIGHT        "Antenna height must be >= 0 meters"
#define LBL__ERROR31_STREET_WIDTH          "Street width must be > 0 meters"
#define LBL__ERROR31_CLUTTER_HEIGHT        "Representative clutter height must be > 0 meters"
#define LBL__ERROR31_CLUTTER_TYPE          "Invalid value for clutter type"
#define LBL__ERROR32_FREQUENCY             "Frequency must be between 2 and 67 GHz, inclusive"
#define LBL__ERROR32_DISTANCE              "Path distance must be >= 0.25 km"
#define LBL__ERROR32_PERCENTAGE            "Percentage must be between 0 and 100"
#define LBL__ERROR33_FREQUENCY             "Frequency must be between 10 and 100 GHz, inclusive"
#define LBL__ERROR33_THETA                 "Elevation angle must be between 0 and 100 GHz, inclusive"
#define LBL__ERROR33_PERCENTAGE            "Percentage must be between 0 and 100, inclusive"

// clang-format on
#endif