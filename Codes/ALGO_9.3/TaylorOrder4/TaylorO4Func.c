#include  "TaylorO4Func.h"

/* Function name      : computeTaylorO4
* Description         : Computes the initial value problem using Taylor Order 4.
* Parameter(s)        : 
*     nLowerLimit           [in]  The lower limit.
*     nUpperLimit           [in]  The upper limit.
*     nInitYValue           [in]  The initial value Y(0).
*     nInterval             [in]  The interval M.
*     funcOfTY[]            [in]  The array of function y',y'',y''',y(4).
*     *pTPoints             [out] Stores the values of t(k).
*     *pYPoints             [out] Stores the values of y(k).
* Return              :     
*    int           - 0  Success. 
*/
int _cdecl 
computeTaylorO4(double nLowerLimit,double nUpperLimit,double nInitYValue,int nInterval,FuncTY funcOfTY[],double *pTPoints,double *pYPoints)
{
    int nRet = 0;
    
    int     i;
    double  nWeightH;

    double  nD1;  /* Result of y'   */
    double  nD2;  /* Result of y''  */
    double  nD3;  /* Result of y''' */
    double  nD4;  /* Result of y(4) */

    /* Clear the pTPoints && pYPoints. */
    memset(pTPoints,0,(nInterval + 1) * sizeof(pTPoints[0]));
    memset(pYPoints,0,(nInterval + 1) * sizeof(pTPoints[0]));
    nWeightH = (nUpperLimit - nLowerLimit) / (double)nInterval;
    /* Set the lower limit is the initial value of t */
    pTPoints[0] = nLowerLimit;
    pYPoints[0] = nInitYValue;
    /* Start the iteration using the Euler's Method */
    for(i = 0; i < nInterval; i++)
    {
        nD1 = funcOfTY[0](pTPoints[i],pYPoints[i]);  /* y'   */
        nD2 = funcOfTY[1](pTPoints[i],pYPoints[i]);  /* y''  */
        nD3 = funcOfTY[2](pTPoints[i],pYPoints[i]);  /* y''' */
        nD4 = funcOfTY[3](pTPoints[i],pYPoints[i]);  /* y(2) */

        pYPoints[i + 1] = pYPoints[i] + 
                          nWeightH * (nD1 + 
                          nWeightH * (nD2 / 2 + nWeightH * (nD3 / 6 + 
                          nWeightH * nD4 / 24)));

        pTPoints[i + 1] = pTPoints[0] + nWeightH * (i+1); 
        
    }

    return nRet;
}

