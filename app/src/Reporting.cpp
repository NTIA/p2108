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
    std::string label;
    switch (clutter_type) {
        case ClutterType::WATER_SEA:
            label = "Water/sea clutter type";
            break;
        case ClutterType::OPEN_RURAL:
            label = "Open/rural clutter type";
            break;
        case ClutterType::SUBURBAN:
            label = "Suburban clutter type";
            break;
        case ClutterType::URBAN:
            label = "Urban clutter type";
            break;
        case ClutterType::TREES_FOREST:
            label = "Trees/forest clutter type";
            break;
        case ClutterType::DENSE_URBAN:
            label = "Dense urban clutter type";
            break;
        default:
            label = "Invalid clutter type";
            break;
    }
    PrintLabel(fp, label);
}