#include "NewtonRaphsonFunc.h"

/* Function name      : computeNewtonRaphson
* Description         : Computes a root of an equation using the newton raphson algorithm.
* Parameter(s)        : 
*     nPn              [in]  The initial value P0.
*     fFunction        [in]  The function to evaluate f(Pn).
*     fFunction1       [in]  The function to evaluate f'(Pn).
*     nMaxIter         [in]  The allowable maximum number of iteration.
*     nPrint           [in]  Flag for printing the output on screen,
*     pOutput          [out]  The root.
*     pDp              [out]  The difference on iteration.
*     pIterCnt         [out]  The actual number of iteration performed.
* Return              :     
*    int     0 -  Success, -1 -  Iteration runout , -2 -  Divide error.
*/
int _cdecl 
computeNewtonRaphson(double nPn,double (*fFunction)(double),double (*fFunction1)(double),int nMaxIter,int nPrint,double *pOutput,double *pDp,int* pIterCnt)
{
    int nRet = -1;                    /* Initialize as iteration runout */      
    static const double nDelta    = 10e-8;  /* Tolerances*/
    static const double nEpsilon  = 10e-8;         
    static const double nSmall    = 10e-8;          
    double nDf;     /* derivative of a function */
    double nDp;     /* f(Pn)/f'(Pn) */
    double nPn1;    /* Pn + 1  */
    double nYn;     /* f(Pn)  */
    double nYn1;    /* f(Pn+1)  */
    int    i;
    double nRelErr;                                
            
    nYn = fFunction(nPn);    /* Compute the function value */
    if(nPrint)
    {
        printf("\n\n N    %-10s  %-10s  %-10s  ","Pn","Pn+1","Ek+1");
        printf("\n------------------------------------------------------------------");
    }
    for(i = 1; i <= nMaxIter && nRet == -1 ; i++)
    {
        nDf = fFunction1(nPn); /* Get the derivative of Pn */
        if(nDf == 0)
        {
            /* Divide error */
            nRet = -2;
            nDp  = 0;
        }
        else
            nDp = nYn/nDf;    

        nPn1  = nPn - nDp;    nYn1  = fFunction(nPn1);

        if(nPrint)
            printf("\n %2d  %2.8lf  %2.8lf  %2.8lf  ",i-1,nPn,nPn1,nPn1 - nPn);

        nRelErr = 2 * fabs(nDp)/(fabs(nPn1) + nSmall);

        if(nRelErr < nDelta && fabs(nYn1) < nEpsilon)
        {
            /* Check for convergence */
            if(nRet != -2)
            {
                nRet = 0;  
                *pOutput = nPn1;
                *pDp     = nDp;
                *pIterCnt = i;
            }
        }

        nPn = nPn1;  nYn = nYn1;
    }
    if(nPrint)
        printf("\n------------------------------------------------------------------");
    return nRet;
}

