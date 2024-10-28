/** @file Enums.h
 * Enumerated types used by this software
 */
#pragma once

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/** Clutter type enum, based on Table 3 in Section 3.1 */
enum ClutterType {
    WATER_SEA = 1,    /**< Water/sea clutter type */
    OPEN_RURAL = 2,   /**< Open/rural clutter type */
    SUBURBAN = 3,     /**< Suburban clutter type */
    URBAN = 4,        /**< Urban clutter type */
    TREES_FOREST = 5, /**< Trees/forest clutter type */
    DENSE_URBAN = 6,  /**< Dense urban clutter type */
};

/**
 * Default values of the representative clutter height @f$ R @f$,
 * in meters, by clutter type.
 *
 * These should be used as inputs to the height gain terminal
 * correction model when local information is not available.
 */
enum RepresentativeClutterHeight {
    R__WATER_SEA = 10,    /**< @f$ R @f$ for the trees/forest clutter type */
    R__OPEN_RURAL = 10,   /**< @f$ R @f$ for the open/rural clutter type */
    R__SUBURBAN = 10,     /**< @f$ R @f$ for the suburban clutter type */
    R__URBAN = 15,        /**< @f$ R @f$ for the urban clutter type */
    R__TREES_FOREST = 15, /**< @f$ R @f$ for the trees/forest clutter type */
    R__DENSE_URBAN = 20,  /**< @f$ R @f$ for the dense urban clutter type */
};

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS
