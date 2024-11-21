/** @file TerrestrialStatisticalModel.cpp
 * Implements the model from ITU-R P.2108 Section 3.2.
 */
#include "P2108.h"

#include <cmath>  // for std::fmin, std::log10, std::pow, std::sqrt

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * Statistical clutter loss model for terrestrial paths as described in
 * Section 3.2.
 *
 * This model can be applied for urban and suburban clutter loss modeling.
 *
 * Frequency range: @f$ 0.5 \leq f \leq 67 @f$ (GHz)\n
 * Path distance range: @f$ 0.25 \leq d @f$ (km) (must be @f$ \geq 1 @f$ to apply
 * the correction at both ends of the path)\n
 * Percentage locations range: @f$0 < p < 100 @f$ (%)
 *
 * @param[in]  f__ghz     Frequency, in GHz
 * @param[in]  d__km      Path distance, in km
 * @param[in]  p          Percentage of locations, in %
 * @param[out] L_ctt__db  Additional loss (clutter loss), in dB
 * @return                Return code
 ******************************************************************************/
ReturnCode TerrestrialStatisticalModel(
    const double f__ghz, const double d__km, const double p, double &L_ctt__db
) {
    const ReturnCode rtn = Section3p2_InputValidation(f__ghz, d__km, p);
    if (rtn != SUCCESS)
        return rtn;

    // compute clutter loss at 2 km
    const double L_ctt_2km__db
        = TerrestrialStatisticalModelHelper(f__ghz, 2, p);

    // compute clutter loss at requested distance
    const double L_ctt_d__db
        = TerrestrialStatisticalModelHelper(f__ghz, d__km, p);

    // "clutter loss must not exceed a maximum value given by [Equation 6]"
    L_ctt__db = std::fmin(L_ctt_2km__db, L_ctt_d__db);

    return SUCCESS;
}

/*******************************************************************************
 * Compute the clutter loss
 *
 * @param[in] f__ghz  Frequency, in GHz
 * @param[in] d__km   Path distance, in km
 * @param[in] p       Percentage of locations, in %
 * @return            Clutter loss, in dB
 ******************************************************************************/
double TerrestrialStatisticalModelHelper(
    const double f__ghz, const double d__km, const double p
) {
    // Equations 4a and 4b
    constexpr double sigma_l__db = 4;
    const double term1 = std::pow(10, -5 * std::log10(f__ghz) - 12.5);
    const double L_l__db = -2 * std::log10(term1 + std::pow(10, -16.5));

    // Equations 5a and 5b
    constexpr double sigma_s__db = 6;
    const double L_s__db
        = 32.98 + 23.9 * std::log10(d__km) + 3 * std::log10(f__ghz);

    // Equation 3b
    const double numerator
        = std::pow(sigma_l__db, 2) * std::pow(10, -0.2 * L_l__db)
        + std::pow(sigma_s__db, 2) * std::pow(10, -0.2 * L_s__db);
    const double denominator
        = std::pow(10, -0.2 * L_l__db) + std::pow(10, -0.2 * L_s__db);
    const double sigma_cb__db = std::sqrt(numerator / denominator);

    // Equation 3a
    const double term2 = std::pow(10, -0.2 * L_l__db);
    const double L_ctt__db
        = -5 * std::log10(term2 + std::pow(10, -0.2 * L_s__db))
        - sigma_cb__db * InverseComplementaryCumulativeDistribution(p / 100);

    return L_ctt__db;
}

/*******************************************************************************
 * Input validation for the statistical clutter loss model for terrestrial paths
 * (Section 3.2).
 *
 * @param[in] f__ghz  Frequency, in GHz
 * @param[in] d__km   Path distance, in km
 * @param[in] p       Percentage of locations, in %
 * @return            Return code
 ******************************************************************************/
ReturnCode Section3p2_InputValidation(
    const double f__ghz, const double d__km, const double p
) {
    if (f__ghz < 0.5 || f__ghz > 67)
        return ERROR32__FREQUENCY;

    if (d__km < 0.25)
        return ERROR32__DISTANCE;

    if (p <= 0 || p >= 100)
        return ERROR32__PERCENTAGE;

    return SUCCESS;
}

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS