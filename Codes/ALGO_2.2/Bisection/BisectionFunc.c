#include "BisectionFunc.h"

/* Function name      : computeBisection
* Description         : Computes the root using the Bisection Method.
* Parameter(s)        : 
*     nA            [in]  Point A.
*     nB            [in]  Point B.
*     fFunction     [in]  The function to evaluate f(x).
*     nPrint        [in]  Flag for printing the output on screen,
*     pOutput       [out]  The root.
*     pAccuracy     [out]  The accuracy of the root.
* Return              :     
*    int        0  - Success, -1 - Same sign.
*/
int _cdecl 
computeBisection(double nA,double nB,double (*fFunction)(double),int nPrint,double *pOutput,double* pAccuracy)
{
    int nRet = 0;
    static const double nDelta  = 10e-8;         /* Tolerance for with of interval */
    int    nSatisfied           = 0;             /* If 1, the calculation is satisfied */ 
    int      i;
    int      nMaxIter;
    double   nYA,nYB,nYC;
    double   nC;
    nYA = fFunction(nA); nYB = fFunction(nB);

    if(GETSIGN(nYA) == GETSIGN(nYB))  nRet = -1;  /* Check for the signs */
    
    if(nRet == 0)
    {
        /* Compute the max number of iterations */
        nMaxIter = 1 + (int)((log(nB - nA) - log(nDelta))/log(2));
        if(nPrint)
        {
            printf("\n The computed max iteration is: %d",nMaxIter);
            printf("\n\n N  %-10s \t %-10s  %-10s  %-8s  %-8s  %-8s  "
                  ,"A","B","C","f(A)","f(B)","f(C)");
            printf("\n---------------------------------------------------------");
        }
        for(i = 1; i <= nMaxIter && nSatisfied == 0 ; i++)
        {
            /* Get the mid point */
            nC = (nA + nB) / 2;
            nYC = fFunction(nC);

            if(nPrint)
                printf("\n %2d  %2.8lf  %2.8lf  %2.8lf  %2.6lf  %2.6lf  %2.6lf "
                      ,i,nA,nB,nC,nYA,nYB,nYC);
            
            if(nYC == 0)  /* Root is found */
            { 
                nA = nC;  nB = nC;    
            } 
            else if(GETSIGN(nYB) == GETSIGN(nYC))
            {
                nB  = nC; nYB = nYC;
            }
            else
            {    
                nA  = nC; nYA = nYC;
            }

            if((nB - nA) < nDelta)
            {
                nSatisfied = 1;
                *pOutput = nC;
                *pAccuracy = (nB - nA);
            }
        }
        if(nPrint)   
            printf("\n-------------------------------------------------------");
    }
    return nRet;
}

