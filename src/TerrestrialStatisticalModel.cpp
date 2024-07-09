/** @file TerrestrialStatisticalModel.cpp
 * Implements the model from ITU-R P.2108 Section 3.2.
*/
#include "ITS.ITU.PSeries.P2108/P2108.h"

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * Statistical clutter loss model for terrestrial paths as described in
 * Section 3.2.
 * 
 * This model can be applied for urban and suburban clutter loss modelling.
 * 
 * @param[in]  f__ghz     Frequency, in GHz
 * @param[in]  d__km      Path distance, in km
 * @param[in]  p          Percentage of locations, in %
 * @param[out] L_ctt__db  Additional loss (clutter loss), in dB
 * @return                Return code
 ******************************************************************************/
int TerrestrialStatisticalModel(double f__ghz, double d__km, double p, double* L_ctt__db)
{
    int rtn = Section3p2_InputValidation(f__ghz, d__km, p);
    if (rtn != SUCCESS)
        return rtn;

    // compute clutter loss at 2 km
    double L_ctt_2km__db = TerrestrialStatisticalModelHelper(f__ghz, 2, p);

    // compute clutter loss at requested distance
    double L_ctt_d__db = TerrestrialStatisticalModelHelper(f__ghz, d__km, p);

    // "clutter loss must not exceed a maximum value given by [Equation 6]"
    *L_ctt__db = fmin(L_ctt_2km__db, L_ctt_d__db);

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
double TerrestrialStatisticalModelHelper(double f__ghz, double d__km, double p)
{
    // Equations 4a and 4b
    double sigma_l__db = 4;
    double L_l__db = -2 * log10(pow(10, -5 * log10(f__ghz) - 12.5) + pow(10, -16.5));

    // Equations 5a and 5b
    double sigma_s__db = 6;
    double L_s__db = 32.98 + 23.9 * log10(d__km) + 3 * log10(f__ghz);

    // Equation 3b
    double numerator = pow(sigma_l__db, 2) * pow(10, -0.2 * L_l__db) + pow(sigma_s__db, 2) * pow(10, -0.2 * L_s__db);
    double denominator = pow(10, -0.2 * L_l__db) + pow(10, -0.2 * L_s__db);
    double sigma_cb__db = sqrt(numerator / denominator);

    // Equation 3a
    double L_ctt__db = -5 * log10(pow(10, -0.2 * L_l__db) + pow(10, -0.2 * L_s__db))
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
int Section3p2_InputValidation(double f__ghz, double d__km, double p)
{
    if (f__ghz < 0.5 || f__ghz > 67)
        return ERROR32__FREQUENCY;

    if (d__km < 0.25)
        return ERROR32__DISTANCE;

    if (p <= 0 || p >= 100)
        return ERROR32__PERCENTAGE;

    return SUCCESS;
}

} } } } // End namespace ITS::ITU::PSeries::P2108