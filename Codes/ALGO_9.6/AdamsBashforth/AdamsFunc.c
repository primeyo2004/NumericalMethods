#include  "AdamsFunc.h"




/* Function name      : computeAdamsBashforthMoulton
* Description         : Computes the initial value problem y' = f(t,y). using AdamsBashforthMoulton
* Parameter(s)        : 
*     nLowerLimit         [in]  The lower limit.
*     nUpperLimit         [in]  The upper limit.
*     nInitYValue[]       [in]  The initial value Y(0) - Y(3).
*     nInterval           [in]  The interval M.
*     pFuncOfTY           [in]  The function y' = f(t,y).
*     *pTPoints           [out] Stores the values of t(k).
*     *pYPoints           [out] Stores the values of y(k).
* Return              :     
*    int           - 0  Success. 
*/
int _cdecl 
computeAdamsBashforthMoulton(double nLowerLimit,double nUpperLimit,double nInitYValue[],int nInterval,double (*pFuncOfTY)(double,double),double *pTPoints,double *pYPoints)
{
    int nRet = 0;
    
    int     i;
    double  nWeightH,nWeightH2,nPredicted;
    double  nF0;  /* Result of f(ti,yi)      */
    double  nF1;  /* Result of f(ti+1,yi+1)  */
    double  nF2;  /* Result of f(ti+2,yi+2)  */
    double  nF3;  /* Result of f(ti+3,yi+3)  */
    double  nF4;  /* Result of f(ti+4,P)     */

    /* Clear the pTPoints && pYPoints. */
    memset(pTPoints,0,(nInterval + 1) * sizeof(pTPoints[0]));
    memset(pYPoints,0,(nInterval + 1) * sizeof(pTPoints[0]));
    nWeightH = (nUpperLimit - nLowerLimit) / (double)nInterval;

    for(i = 0; i <= 3; i++)
    {
        pTPoints[i] = nLowerLimit + nWeightH * i;
        pYPoints[i] = nInitYValue[i];
    }
    /* Get the respective results */
    nF0 = pFuncOfTY(pTPoints[0],pYPoints[0]);
    nF1 = pFuncOfTY(pTPoints[1],pYPoints[1]);
    nF2 = pFuncOfTY(pTPoints[2],pYPoints[2]);
    nF3 = pFuncOfTY(pTPoints[3],pYPoints[3]);
    
    nWeightH2 = nWeightH/24;
    /* Start the iteration using the Euler's Method */
    for(i = 3; i < nInterval; i++)
    {
        /* Compute the predicted value */
        nPredicted = pYPoints[i] + nWeightH2 * (-9 * nF0 + 37 * nF1 - 59 * nF2 + 55 * nF3);
        pTPoints[i+1] = nLowerLimit + nWeightH * (i + 1);

        nF4 = pFuncOfTY(pTPoints[i+1],nPredicted);
        /* Compute the Y(i+1) */
        pYPoints[i + 1] = pYPoints[i] + nWeightH2 * (nF1 - 5 * nF2 + 19 * nF3 + 9 * nF4);

        /* Roll the values down */
        nF0 = nF1; nF1 = nF2;  nF2 = nF3;  nF3 = pFuncOfTY(pTPoints[i+1],pYPoints[i+1]);;
        
    }

    return nRet;
}

