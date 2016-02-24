#include "CompTrapFunc.h"

/* Function name       : computeCompTrapezoidal
* Description         : Computes the numerical intergal of a function  using the
*                       Composite Trapezoidal Rule.
* Parameter(s)        : 
*     nLowerLimit        [in]  The lower limit of intergration.
*     nUpperLimit        [in]  The upper limit of integration.
*     nInterval          [in]  The number of interval for intergration.
*     funcOfX            [in]  Pointer to the function the will evalute the f(x).
*     *pResult           [out] The integration result.
* Return              :     
*    int           0 -  Success
*/
int _cdecl
computeCompTrapezoidal(double nLowerLimit,double nUpperLimit,int nInterval, double (*funcOfX)(double nX),double *pResult)
{
    int nRet = 0;

    double nWeightH;
    double nSum;

    int   i;

    nWeightH = (nUpperLimit - nLowerLimit) / (double) nInterval;

    nSum = 0;

    /* Compute first the summation */
    for(i = 1; i <= (nInterval - 1); i++)
    {
        double nX;    

        nX = nLowerLimit + nWeightH * i;

        /* Compute using the passed function of x */
        nSum += funcOfX(nX);
    }


    *pResult = nWeightH * (funcOfX(nLowerLimit) + funcOfX(nUpperLimit) + nSum * 2)/2;


    return nRet;
}



