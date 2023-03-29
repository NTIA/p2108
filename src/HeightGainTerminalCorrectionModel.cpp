#include "../include/P2108.h"
#include "../include/Errors.h"
#include "../include/Consts.h"

/*=============================================================================
 |
 |  Description:  Height gain terminal correction model as described in
 |                Section 3.1.  This method gives the median loss due to 
 |                different terminal surroundings.  This model can be
 |                applied to both transmitting and receiving ends of the path.
 |
 |        Input:  f__ghz        - Frequency, in GHz
 |                h__meter      - Antenna height, in meters
 |                w_s__meter    - Street width, in meters
 |                R__meter      - Representative clutter height, in meters
 |                clutter_type  - Clutter type
 |
 |       Output:  A_h__db       - Additional loss (clutter loss), in dB
 |
 |      Returns:  error         - Error code
 |
 *===========================================================================*/
int HeightGainTerminalCorrectionModel(double f__ghz, double h__meter, 
    double w_s__meter, double R__meter, int clutter_type, double *A_h__db)
{
    int rtn = Section3p1_InputValidation(f__ghz, h__meter, w_s__meter, R__meter);
    if (rtn != SUCCESS)
        return rtn;

    double h_dif__meter = R__meter - h__meter;                              // Equation (2d)
    double theta_clut__deg = atan(h_dif__meter / w_s__meter) * 180.0 / PI;  // Equation (2e)
    double K_h2 = 21.8 + 6.2 * log10(f__ghz);                               // Equation (2f)

    switch (clutter_type)
    {
    case CLUTTER_TYPE__WATER_SEA:
    case CLUTTER_TYPE__OPEN_RURAL:
        *A_h__db = Equation_2b(K_h2, h__meter, R__meter);
        break;
        
    case CLUTTER_TYPE__SUBURBAN:
    case CLUTTER_TYPE__URBAN:
    case CLUTTER_TYPE__TREES_FOREST:
    case CLUTTER_TYPE__DENSE_URBAN:
    {
        double K_nu = 0.342 * sqrt(f__ghz);                         // Equation (2g)
        double nu = K_nu * sqrt(h_dif__meter * theta_clut__deg);    // Equation (2c)

        *A_h__db = Equation_2a(nu);
        break;
    }
    default:
        return ERROR31__CLUTTER_TYPE;
    }

    return SUCCESS;
}

/*=============================================================================
 |
 |  Description:  Input validation for the height gain terminal correction
 |                model (Section 3.1).
 |                Note: Input parameter 'clutter_type' is validated in
 |                the main function's switch statement through the use
 |                of default to simplify code structure.
 |
 |        Input:  f__ghz        - Frequency, in GHz
 |                h__meter      - Antenna height, in meters
 |                w_s__meter    - Street width, in meters
 |                R__meter      - Representative clutter height, in meters
 |
 |      Returns:  error code or SUCCESS
 |
 *===========================================================================*/
int Section3p1_InputValidation(double f__ghz, double h__meter, double w_s__meter, 
    double R__meter)
{
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

/*=============================================================================
 |
 |  Description:  Equation (2a) of Section 3.1
 |
 |        Input:  nu            - Dimensionless diffraction parameter
 |
 |      Returns:  A_h__db       - Additional loss (clutter loss), in dB
 |
 *===========================================================================*/
double Equation_2a(double nu)
{
    double J_nu__db;
    if (nu <= -0.78)
        J_nu__db = 0;
    else
        J_nu__db = 6.9 + 20 * log10(sqrt(pow(nu - 0.1, 2) + 1) + nu - 0.1);

    double A_h__db = J_nu__db - 6.03;

    return A_h__db;
}

/*=============================================================================
 |
 |  Description:  Equation (2b) of Section 3.1
 |
 |        Input:  K_h2          - Intermediate parameter
 |                h__meter      - Antenna height, in meters
 |                R__meter      - Representative clutter height, in meters
 |
 |      Returns:  A_h__db       - Additional loss (clutter loss), in dB
 |
 *===========================================================================*/
double Equation_2b(double K_h2, double h__meter, double R__meter)
{
    double A_h__db = -K_h2 * log10(h__meter / R__meter);

    return A_h__db;
}