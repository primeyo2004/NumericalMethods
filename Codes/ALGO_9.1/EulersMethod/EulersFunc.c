#include  "EulersFunc.h"

/* Function name       : computeEulersMethod
* Description          :  Computes the initial value problem y' = f(t,y) using
*                         Euler's method.   
* Parameter(s)         : 
*     nLowerLimit       [in]  The lower limit.
*     nUpperLimit       [in]  The upper limit.
*     nInitYValue       [in]  The initial value Y(0).
*     nInterval         [in]  The interval M.
*     pFuncOfTY         [in]  The function y' = f(t,y).
*     *pTPoints         [out] Stores the values of t(k).
*     *pYPoints         [out] Stores the values of y(k).
* Return              :     
*    int           - 0  Success. 
*/
int _cdecl 
computeEulersMethod(double nLowerLimit,double nUpperLimit,double nInitYValue,int nInterval,double (*pFuncOfTY)(double t,double y),double *pTPoints,double *pYPoints)
{
    int nRet = 0;
    
    int     i;
    double  nWeightH;

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
        pYPoints[i+1] = pYPoints[i] + nWeightH * pFuncOfTY(pTPoints[i],pYPoints[i]);
        pTPoints[i+1] = nLowerLimit + nWeightH * (i+1);
    }

	return nRet;
}

