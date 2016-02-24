#include "FalsePositionFunc.h"
/* 
* Function name       : computeFalsePosition
* Description         : Computes the root using the false position method.
* Parameter(s)        : 
*     nA            [in]  Point A.
*     nB            [in]  Point B.
*     fFunction     [in]  The function to evaluate f(x).
*     nMaxIter      [in]  The maximum number of iteration.
*     nPrint        [in]  Flag for printing the output on screen,
*     pOutput       [out] The root.
*     pDx           [out] The difference between the iteration.
* Return              :     
*    int        0  - Success, -1 - Same sign.
*/
int _cdecl 
computeFalsePosition(double nA,double nB,double (*fFunction)(double),int nMaxIter,int nPrint,double *pOutput,double* pDx)
{
    int nRet = 0;
    static const double nDelta    = 10e-8;         /* Tolerance for change in X */
    static const double nEpsilon  = 10e-8;         /* Tolerance for f(C) */
    double nDx  = 0;                               /* Change in X */
    int    nSatisfied           = 0;               /* If 1, the calculation is satisfied */ 
    int      i;
    double   nYA,nYB,nYC,nC;

    nYA = fFunction(nA);  nYB = fFunction(nB);
    if(GETSIGN(nYA) == GETSIGN(nYB)) nRet = -1; /* Check for the signs */
    
    if(nRet == 0)
    {
        if(nPrint)
        {
            printf("\n\n N  %-10s \t %-10s  %-10s  %-8s  %-8s  %-8s  "
                   ,"A","B","C","f(A)","f(B)","f(C)");
            printf("\n--------------------------------------------------------------");
        }
        for(i = 1; i <= nMaxIter && nSatisfied == 0 ; i++)
        {
            /* Get the change in X */
            nDx = nYB * (nB-nA) /(nYB- nYA);
            nC  = nB - nDx;

            nYC = fFunction(nC);
            if(nPrint)
                printf("\n %2d  %2.8lf  %2.8lf  %2.8lf  %2.6lf  %2.6lf  %2.6lf "
                       ,i,nA,nB,nC,nYA,nYB,nYC);
            if(nYC == 0)
            {
                nSatisfied = 1; /* Root is found */
            }
            else if(GETSIGN(nYB) == GETSIGN(nYC))
            {
                nB  = nC;  nYB = nYC;
            }
            else
            {    
                nA  = nC;  nYA = nYC;
            }

            if(fabs(nDx) < nDelta && fabs(nYC) < nEpsilon)
            {
                nSatisfied = 1;
                *pOutput = nC;
                *pDx     = nDx;
            }
        }

        if(nPrint)
             printf("\n-------------------------------------------------------------");
    }
    
    return nRet;
}

