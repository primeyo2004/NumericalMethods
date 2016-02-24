#include  "RungeKuttaFunc.h"



/*--------------------------------------------------------------------------------*
* Function name       : computeRungeKutta
* Description         : Computes the initial value problem y' = f(t,y). using Rung-Kutta of Order 4.
*                       
* Parameter(s)        : 
*	 nLowerLimit		 [in]  The lower limit.
*                       
*	 nUpperLimit		 [in]  The upper limit.
*                       
*	 nInitYValue		 [in]  The initial value Y(0).
*                       
*	 nInterval		     [in]  The interval M.
*                       
*	 pFuncOfTY   		 [in]  The function y' = f(t,y).
*                       
*	 *pTPoints		     [out] Stores the values of t(k).
*                       
*	 *pYPoints		     [out] Stores the values of y(k).
*                       
* Return              :     
*    int           - 0  Success. 
*                 
* Author              : Prime
*                 
* Revision(s)         :         
* 0.0.0 	Prime	3/1/2004	Initial release.
*--------------------------------------------------------------------------------*/
int _cdecl 
computeRungeKutta(double nLowerLimit,double nUpperLimit,double nInitYValue,int nInterval,double (*pFuncOfTY)(double,double),double *pTPoints,double *pYPoints)
{
	int nRet = 0;
	
	int     i;
	double  nWeightH;

	double  nK1;  /* Result of f(t,y) @ ti     */
	double  nK2;  /* Result of f(t,y) @ ti.5   */
	double  nK3;  /* Result of f(t,y) @ ti+.5  */
	double  nK4;  /* Result of f(t,y) @ ti+1   */


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
		nK1 = nWeightH * pFuncOfTY(pTPoints[i],pYPoints[i]);                               /* f(t,y) @ ti       */
		nK2 = nWeightH * pFuncOfTY(pTPoints[i] + (nWeightH/2),pYPoints[i] + (0.5 * nK1));  /* f(t,y) @ ti + .5  */
		nK3 = nWeightH * pFuncOfTY(pTPoints[i] + (nWeightH/2),pYPoints[i] + (0.5 * nK2));  /* f(t,y) @ ti + .5  */
		nK4 = nWeightH * pFuncOfTY(pTPoints[i] + nWeightH,pYPoints[i] + nK3);              /* f(t,y) @ ti+1     */

		pYPoints[i + 1] = pYPoints[i] + (nK1 + 2*nK2 + 2*nK3 + nK4)/6;
		pTPoints[i + 1] = pTPoints[0] + nWeightH * (i+1); 
		
	}

	return nRet;
}

