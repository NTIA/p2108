/** @file HeightGainTerminalCorrectionModel.cpp
 * Implements the model from ITU-R P.2108 Section 3.1.
 */
#include "P2108.h"

#include <cmath>  // for std::atan, std::log10, std::pow, std::sqrt

namespace ITS {
namespace ITU {
namespace PSeries {
namespace P2108 {

/*******************************************************************************
 * Height gain terminal correction model as described in Section 3.1.
 *
 * This method gives the median loss due to different terminal surroundings.
 * This model can be applied to both transmitting and receiving ends of the
 * path.
 *
 * Frequency range: @f$ 0.03 \leq f \leq 3 @f$ (GHz)\n
 * Antenna height range: @f$ 0 \leq h @f$ (m)\n
 * Street width range: @f$ 0 < w_s @f$ (m)\n
 * Representative clutter height range: @f$ 0 < R @f$ (m)
 *
 * @param[in]  f__ghz        Frequency, in GHz
 * @param[in]  h__meter      Antenna height, in meters
 * @param[in]  w_s__meter    Street width, in meters
 * @param[in]  R__meter      Representative clutter height, in meters
 * @param[in]  clutter_type  Clutter type
 * @param[out] A_h__db       Additional loss (clutter loss), in dB
 * @return                   Return code
 ******************************************************************************/
ReturnCode HeightGainTerminalCorrectionModel(
    const double f__ghz,
    const double h__meter,
    const double w_s__meter,
    const double R__meter,
    const ClutterType clutter_type,
    double &A_h__db
) {
    const ReturnCode rtn
        = Section3p1_InputValidation(f__ghz, h__meter, w_s__meter, R__meter);
    if (rtn != SUCCESS)
        return rtn;

    if (h__meter >= R__meter) {
        A_h__db = 0;
        return SUCCESS;
    }

    const double h_dif__meter = R__meter - h__meter;  // Equation (2d)
    const double theta_clut__deg
        = std::atan(h_dif__meter / w_s__meter) * 180.0 / PI;  // Equation (2e)
    const double K_h2 = 21.8 + 6.2 * std::log10(f__ghz);      // Equation (2f)

    switch (clutter_type) {
        case ClutterType::WATER_SEA:
        case ClutterType::OPEN_RURAL:
            A_h__db = Equation_2b(K_h2, h__meter, R__meter);
            break;

        case ClutterType::SUBURBAN:
        case ClutterType::URBAN:
        case ClutterType::TREES_FOREST:
        case ClutterType::DENSE_URBAN:
            {
                const double K_nu = 0.342 * std::sqrt(f__ghz);  // Equation (2g)
                const double nu = K_nu
                                * std::sqrt(
                                      h_dif__meter * theta_clut__deg
                                );  // Equation (2c)

                A_h__db = Equation_2a(nu);
                break;
            }
        default:
            return ERROR31__CLUTTER_TYPE;
    }

    return SUCCESS;
}

/*******************************************************************************
 * Input validation for the height gain terminal correction model (Section 3.1).
 *
 * Note: Input parameter 'clutter_type' is validated in the main function's
 * switch statement through the use of default to simplify code structure.
 *
 * @param[in] f__ghz      Frequency, in GHz
 * @param[in] h__meter    Antenna height, in meters
 * @param[in] w_s__meter  Street width, in meters
 * @param[in] R__meter    Representative clutter height, in meters
 * @return                Return code
 ******************************************************************************/
ReturnCode Section3p1_InputValidation(
    const double f__ghz,
    const double h__meter,
    const double w_s__meter,
    const double R__meter
) {
    if (f__ghz < 0.03 || f__ghz > 3)
        return ERROR31__FREQUENCY;

    if (h__meter <= 0)
        return ERROR31__ANTENNA_HEIGHT;

    if (w_s__meter <= 0)
        return ERROR31__STREET_WIDTH;

    if (R__meter <= 0)
        return ERROR31__CLUTTER_HEIGHT;

    return SUCCESS;
}

/*******************************************************************************
 * Equation (2a) of Section 3.1
 *
 * @param[in] nu  Dimensionless diffraction parameter
 * @return        Additional loss (clutter loss), in dB
 ******************************************************************************/
double Equation_2a(const double nu) {
    double J_nu__db;
    if (nu <= -0.78) {
        J_nu__db = 0;
    } else {
        const double term1 = std::sqrt(std::pow(nu - 0.1, 2) + 1);
        J_nu__db = 6.9 + 20 * std::log10(term1 + nu - 0.1);
    }
    const double A_h__db = J_nu__db - 6.03;

    return A_h__db;
}

/*******************************************************************************
 * Equation (2b) of Section 3.1
 *
 * @param[in] K_h2      Intermediate parameter
 * @param[in] h__meter  Antenna height, in meters
 * @param[in] R__meter  Representative clutter height, in meters
 * @return              Additional loss (clutter loss), in dB
 ******************************************************************************/
double Equation_2b(
    const double K_h2, const double h__meter, const double R__meter
) {
    const double A_h__db = -K_h2 * std::log10(h__meter / R__meter);

    return A_h__db;
}

}  // namespace P2108
}  // namespace PSeries
}  // namespace ITU
}  // namespace ITS