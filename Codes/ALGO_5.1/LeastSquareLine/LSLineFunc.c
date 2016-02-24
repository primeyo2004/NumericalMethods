#include "LSLineFunc.h"
/* Function name       : computeLSLine
* Description         : Computes the coefficients A and B for a Least Square Line.
* Parameter(s)        : 
*     *pXPoints         [in]  The X coordinate vector.
*     *pYPoints         [in]  The Y coordinate vector corresponding to each point in X.
*     nNumPoints        [in]  The number of elements or data points.
*     pA                 [out] The A coefficient.
*     pB                 [out] The B coefficient.
* Return              :     
*    int _cdecl       0  - Success, -1  - Insufficient data points.
*/
int _cdecl 
computeLSLine(double *pXPoints,double *pYPoints,int nNumPoints,double* pA,double* pB)
{
    int nRet = -1;
    double    nSumXSqrd;  /*  Sum (X^2) */
    double    nSumXY;     /*  Sum (XY)  */
    double    nSumX;      /*  Sum (X)   */
    double    nSumY;      /*  Sum (Y)   */
    double    nDet;       /*  The determinant   */
    int       i;
    *pA = 0;
    *pB = 0;
    /* Must require atleast two points */
    if(nNumPoints > 1)
    {
        nSumXSqrd = 0; 
        nSumXY    = 0; 
        nSumX     = 0; 
        nSumY     = 0; 
        /* Find the summation values */
        for(i = 0; i < nNumPoints; i ++)
        {
            nSumXSqrd += pXPoints[i] * pXPoints[i];  /* Sum up all the x^2 */
            nSumXY    += pXPoints[i] * pYPoints[i];  /* Sum up all the xy  */
            nSumX     += pXPoints[i];                /* Sum up all the x  */
            nSumY     += pYPoints[i];                /* Sum up all the y  */  
        }
        /* Get the value for A using cramer's rule */
        nDet = nNumPoints * nSumXSqrd - nSumX * nSumX;
        if(nDet == 0)  nRet = -2;
        else           nRet = 0;
    }

    if(nRet == 0)
    {
        *pA = (nNumPoints * nSumXY - nSumX * nSumY) / nDet;
        *pB = (nSumXSqrd * nSumY - nSumX * nSumXY) / nDet;

        nRet = 0;
    }

    return nRet;
}