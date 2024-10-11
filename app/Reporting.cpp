/** @file Reporting.cpp
 * Implements utility functions for printing driver results
 */
#include "Driver.h"
#include "Labels.h"
#include "Tags.h"

/*******************************************************************************
 * Print text message corresponding to clutter type enum value
 * 
 * @param[in] fp            Output stream, a text file open for writing
 * @param[in] clutter_type  Height Gain Terminal Correction Model clutter type
 ******************************************************************************/
void PrintClutterTypeLabel(std::ofstream &fp, const ClutterType clutter_type) {
    switch (clutter_type) {
        case ClutterType::WATER_SEA:
            PrintLabel(fp, LBL__CLUTTERTYPE_WATER_SEA);
            break;
        case ClutterType::OPEN_RURAL:
            PrintLabel(fp, LBL__CLUTTERTYPE_OPEN_RURAL);
            break;
        case ClutterType::SUBURBAN:
            PrintLabel(fp, LBL__CLUTTERTYPE_SUBURBAN);
            break;
        case ClutterType::URBAN:
            PrintLabel(fp, LBL__CLUTTERTYPE_URBAN);
            break;
        case ClutterType::TREES_FOREST:
            PrintLabel(fp, LBL__CLUTTERTYPE_TREES_FOREST);
            break;
        case ClutterType::DENSE_URBAN:
            PrintLabel(fp, LBL__CLUTTERTYPE_DENSE_URBAN);
            break;
        default:
            PrintLabel(fp, LBL__ERROR_INVALID_VALUE);
            break;
    }
}

/*******************************************************************************
 * Helper function to standardize printing of text labels to file
 * 
 * @param[in] fp   Output stream, a text file open for writing
 * @param[in] lbl  Text message
 ******************************************************************************/
void PrintLabel(std::ofstream &fp, const char *lbl) {
    fp << "[" << lbl << "]";
}
