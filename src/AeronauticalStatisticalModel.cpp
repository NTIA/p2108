#include "../include/ITS.ITU.PSeries.P2108/P2108.h"
#include "../include/ITS.ITU.PSeries.P2108/Errors.h"

/*=============================================================================
 |
 |  Description:  The Earth-space and aeronautical statistical clutter loss
 |                model as described in Section 3.3.  This model is applicable
 |                when one end of the path is within man-made clutter and the
 |                other end is a satellite, aeroplane, or other platform
 |                above the Earth.
 |
 |        Input:  f__ghz        - Frequency, in GHz
 |                theta__deg    - Elevation angle, in degrees
 |                p             - Percentage of locations, in %
 |
 |       Output:  L_ces__db     - Additional loss (clutter loss), in dB
 |
 |      Returns:  error         - Error code
 |
 *===========================================================================*/
int AeronauticalStatisticalModel(double f__ghz, double theta__deg, double p,
    double* L_ces__db)
{
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

/*=============================================================================
 |
 |  Description:  Input validation for the Earth-space and aeronautical 
 |                statistical clutter loss model (Section 3.3).
 |
 |        Input:  f__ghz        - Frequency, in GHz
 |                theta__deg    - Elevation angle, in degrees
 |                p             - Percentage of locations, in %
 |
 |      Returns:  error code or SUCCESS
 |
 *===========================================================================*/
int Section3p3_InputValidation(double f__ghz, double theta__deg, double p)
{
    if (f__ghz < 10 || f__ghz > 100)
        return ERROR33__FREQUENCY;

    if (theta__deg < 0 || theta__deg > 90)
        return ERROR33__THETA;

    if (p <= 0 || p >= 100)
        return ERROR33__PERCENTAGE;

    return SUCCESS;
}

/*=============================================================================
 |
 |  Description:  Helper function for cotangent operation.
 |
 |        Input:  x             - Argument
 |
 |      Returns:  cot(x)        - Cotangent of the argument
 |
 *===========================================================================*/
double cot(double x)
{
    return 1 / tan(x);
}