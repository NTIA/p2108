/** @internal @file InverseComplementaryCumulativeDistribution.cpp
 * @brief Implements a function to calculate the inverse CCDF.
 */
#include "ITS.ITU.PSeries.P2108/P2108.h"

#include <stdexcept>

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * Compute the inverse complementary cumulative distribution function
 * approximation as described in Recommendation ITU-R P.1057.
 *
 * This approximation is sourced from Formula 26.2.23 in Abramowitz & Stegun.
 * This approximation has an error of @f$ |\epsilon(p)| < 4.5\times 10^{-4} @f$
 *
 * @param q  Percentage, @f$ 0.0 < q < 1.0 @f$
 * @return   Q(q)^-1
 * @throw std::out_of_range if the input is outside the range [0.0, 1.0]
 ******************************************************************************/
double InverseComplementaryCumulativeDistribution(double q) {
    if (q <= 0.0 || q >= 1.0) {
        throw std::out_of_range("Input q must be between 0.0 and 1.0");
    }

    // Constants from Abramowitz & Stegun 26.2.23
    double C_0 = 2.515517;
    double C_1 = 0.802853;
    double C_2 = 0.010328;
    double D_1 = 1.432788;
    double D_2 = 0.189269;
    double D_3 = 0.001308;

    double x = q;
    if (q > 0.5)
        x = 1.0 - x;

    double T_x = sqrt(-2.0 * log(x));

    double zeta_x = ((C_2 * T_x + C_1) * T_x + C_0)
                  / (((D_3 * T_x + D_2) * T_x + D_1) * T_x + 1.0);

    double Q_q = T_x - zeta_x;

    if (q > 0.5)
        Q_q = -Q_q;

    return Q_q;
}

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS