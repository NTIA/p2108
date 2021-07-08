#include "..\include\P2108.h"
#include "..\include\Errors.h"

/*=============================================================================
 |
 |  Description:  Statistical clutter loss model for terrestrial paths as
 |                described in Section 3.2.  This model can be applied
 |                for urban and suburban clutter loss modelling.
 |
 |        Input:  f__ghz        - Frequency, in GHz
 |                d__km         - Path distance, in km
 |                p             - Percentange of locations, in %
 |
 |       Output:  L_ctt__db     - Additional loss (clutter loss), in dB
 |
 |      Returns:  error         - Error code
 |
 *===========================================================================*/
int TerrestrialStatisticalModel(double f__ghz, double d__km, double p, double* L_ctt__db)
{
    int rtn = Section3p2_InputValidation(f__ghz, d__km, p);
    if (rtn != SUCCESS)
        return rtn;

    double L_l__db = 23.5 + 9.6 * log10(f__ghz);                        // Equation 4
    double L_s__db = 32.98 + 23.9 * log10(d__km) + 3 * log10(f__ghz);   // Equation 5

    *L_ctt__db = -5 * log10(pow(10, -0.2 * L_l__db) + pow(10, -0.2 * L_s__db))
        - 6 * InverseComplementaryCumulativeDistribution(p / 100);

    return SUCCESS;
}

/*=============================================================================
 |
 |  Description:  Input validation for the statistical clutter loss model
 |                for terrestrial paths (Section 3.2).
 |
 |        Input:  f__ghz        - Frequency, in GHz
 |                d__km         - Path distance, in km
 |                p             - Percentange of locations, in %
 |
 |      Returns:  error code or SUCCESS
 |
 *===========================================================================*/
int Section3p2_InputValidation(double f__ghz, double d__km, double p)
{
    if (f__ghz < 2 || f__ghz > 67)
        return ERROR32__FREQUENCY;

    if (d__km < 0.25)
        return ERROR32__DISTANCE;

    if (p <= 0 || p >= 100)
        return ERROR32__PERCENTAGE;

    return SUCCESS;
}