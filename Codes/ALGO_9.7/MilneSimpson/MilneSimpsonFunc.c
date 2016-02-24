#include  "MilneSimpsonFunc.h"

/* Function name       : computeMilneSimpson
* Description          : Computes the initial value problem y' = f(t,y). using Milne - Simpson Method
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
computeMilneSimpson(double nLowerLimit,double nUpperLimit,double nInitYValue[],int nInterval,double (*pFuncOfTY)(double,double),double *pTPoints,double *pYPoints)
{
    int nRet = 0;
   
    int     i;
    double  nWeightH;
    double  nPredictedOld;
    double  nPredictedNew;
    double  nPredictedMod;
    double  nYOld;
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
    nF1 = pFuncOfTY(pTPoints[1],pYPoints[1]);
    nF2 = pFuncOfTY(pTPoints[2],pYPoints[2]);
    nF3 = pFuncOfTY(pTPoints[3],pYPoints[3]);

    nPredictedOld = 0;
    nYOld  = 0;

    /* Start the iteration using the Euler's Method */
    for(i = 3; i < nInterval; i++)
    {
        /* Compute the predicted value */
        nPredictedNew = pYPoints[i-3] + 4 * nWeightH * (2 * nF1 - nF2 + 2 * nF3)/3;
        nPredictedMod = nPredictedNew + 28 * (nYOld - nPredictedOld)/29;
        pTPoints[i+1] = nLowerLimit + nWeightH * (i + 1);
        nF4 = pFuncOfTY(pTPoints[i+1],nPredictedMod);
        /* Compute the Y(i+1) */
        pYPoints[i + 1] = pYPoints[i-1] + nWeightH * (nF2 + 4 * nF3 + nF4)/3;
        nPredictedOld = nPredictedNew;
        nYOld = pYPoints[i + 1];
        /* Roll the values down */
        nF1 = nF2;  nF2 = nF3;  nF3 = pFuncOfTY(pTPoints[i+1],pYPoints[i+1]);
    }

    return nRet;
}

