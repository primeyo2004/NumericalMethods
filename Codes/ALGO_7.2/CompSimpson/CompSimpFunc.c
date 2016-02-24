#include "CompSimpFunc.h"

/* Function name       : computeCompSimpson
* Description         : Computes the numerical intergal of a function  using the
*                       Composite Simpson's Rule.
* Parameter(s)        : 
*     nLowerLimit        [in]  The lower limit of intergration.
*     nUpperLimit        [in]  The upper limit of integration.
*     nInterval          [in]  The number of interval for intergration.
*     funcOfX            [in]  Pointer to the function the will evaluate the f(x).
*     *pResult           [out] The integration result.
* Return              :     
*    int  0 - Success
*/
int _cdecl
computeCompSimpson(double nLowerLimit,double nUpperLimit,int nInterval, double (*funcOfX)(double nX),double *pResult)
{
    int nRet = 0;

    double nWeightH;
    double nSumEven;
    double nSumOdd;
    int   i;
    nWeightH = (nUpperLimit - nLowerLimit) / (double) (nInterval * 2);

    nSumEven = 0;
    /* Compute the summation of even intervals */
    for(i = 1; i <= (nInterval - 1); i++)
    {
        double nX;    

        nX = nLowerLimit + nWeightH * 2 * i;

        /* Compute using the passed function of x */
        nSumEven += funcOfX(nX);
    }

    nSumOdd = 0;
    /* Compute the summation of odd intervals */
    for(i = 1; i <= nInterval; i++)
    {
        double nX;    

        nX = nLowerLimit + nWeightH * (2 * i - 1);

        /* Compute using the passed function of x */
        nSumOdd += funcOfX(nX);
    }

    *pResult = nWeightH * (funcOfX(nLowerLimit) + funcOfX(nUpperLimit) + (nSumEven * 2) + (nSumOdd * 4))/3;

    return nRet;
}



