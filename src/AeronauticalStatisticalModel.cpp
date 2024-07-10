/** @file AeronauticalStatisticalModel.cpp
 * Implements the model from ITU-R P.2108 Section 3.3.
 */
#include "ITS.ITU.PSeries.P2108/P2108.h"

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * The Earth-space and aeronautical statistical clutter loss model as described
 * in Section 3.3.
 *
 * This model is applicable when one end of the path is within man-made clutter
 * and the other end is a satellite, aeroplane, or other platform above the
 * Earth.
 *
 * Frequency range: @f$ 10 < f < 100 @f$ (GHz)\n
 * Elevation angle range: @f$ 0 < \theta < 90 @f$ (degrees)\n
 * Percentage locations range: @f$ 0 < p < 100 @f$ (%)
 *
 * @param[in]  f__ghz      Frequency, in GHz
 * @param[in]  theta__deg  Elevation angle, in degrees
 * @param[in]  p           Percentage of locations, in %
 * @param[out] L_ces__db   Additional loss (clutter loss), in dB
 * @return                 Return code
 ******************************************************************************/
int AeronauticalStatisticalModel(
    double f__ghz, double theta__deg, double p, double *L_ces__db
) {
    int rtn = Section3p3_InputValidation(f__ghz, theta__deg, p);
    if (rtn != SUCCESS)
        return rtn;

    double A_1 = 0.05;
    double K_1 = 93 * pow(f__ghz, 0.175);

    double part1 = log(1 - p / 100.0);
    double part2 = A_1 * (1 - theta__deg / 90.0) + PI * theta__deg / 180.0;
    double part3 = 0.5 * (90.0 - theta__deg) / 90.0;
    double part4 = 0.6 * InverseComplementaryCumulativeDistribution(p / 100);

    *L_ces__db = pow(-K_1 * part1 * cot(part2), part3) - 1 - part4;

    return SUCCESS;
}

/*******************************************************************************
 * Inputs-in-range validation for the Earth-space and aeronautical statistical
 * clutter loss model (Section 3.3).
 *
 * Returns `SUCCESS` if all parameters are valid. Otherwise, invalid inputs will
 * return unique error codes.
 *
 * Frequency range: @f$ 10 < f < 100 @f$ (GHz)\n
 * Elevation angle range: @f$ 0 < \theta < 90 @f$ (degrees)\n
 * Percentage locations range: @f$ 0 < p < 100 @f$ (%)
 *
 * @param[in] f__ghz      Frequency, in GHz
 * @param[in] theta__deg  Elevation angle, in degrees
 * @param[in] p           Percentage of locations, in %
 * @return                Return code
 ******************************************************************************/
int Section3p3_InputValidation(double f__ghz, double theta__deg, double p) {
    if (f__ghz < 10 || f__ghz > 100)
        return ERROR33__FREQUENCY;

    if (theta__deg < 0 || theta__deg > 90)
        return ERROR33__THETA;

    if (p <= 0 || p >= 100)
        return ERROR33__PERCENTAGE;

    return SUCCESS;
}

/*******************************************************************************
 * Helper function to calculate @f$ \cot(x) @f$.
 *
 * The calculation is implemented simply as @f$ 1 / \cot(x) @f$.
 *
 * @param[in] x  Argument, in radians
 * @return       Cotangent of the argument, @f$ \cot(x) @f$
 ******************************************************************************/
double cot(double x) {
    return 1 / tan(x);
}

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS