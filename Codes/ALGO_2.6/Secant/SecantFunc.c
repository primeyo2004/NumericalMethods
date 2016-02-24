#include "SecantFunc.h"
/* Function name       : computeSecant
* Description         : Computes a root of an equation using the secant method.
* Parameter(s)        : 
*     nPn             [in]  The initial value P0.
*     nPn1            [in]  The initial value P1.
*     *fFunction      [in]  The function to evaluate f(Pn).
*     nMaxIter        [in]  The maximum number of iteration.
*     nPrint          [in]  Flag for printing the output on screen,
*     pOutput         [out]  The root.
*     pDp             [out]  The difference on iteration.
*     pIterCnt        [out]  The actual number of iteration performed.
* Return              :     
*    int     0 -  Success, -1 -  Iteration has runout, -2 -  Divide error.
*/
int _cdecl 
computeSecant(double nPn,double nPn1,double (*fFunction)(double),int nMaxIter,int nPrint,double *pOutput,double *pDp,int* pIterCnt)
{
    int nRet = -1;                                 /* Initialize as iteration runout */      
    static const double nDelta    = 10e-8;         /* Tolerances*/
    static const double nEpsilon  = 10e-8;         
    static const double nSmall    = 10e-8;          
    double nDf;                                    /* Slope    */
    double nDp;                                    /* Y1/slope */
    double nPn2;                                   /* Pn+2   */
    double nYn;                                    /* f(Pn)  */
    double nYn1;                                   /* f(Pn+1)  */
    double nYn2;                                   /* f(Pn+2)  */
    int    i;
    double nRelErr;                                
    nYn  = fFunction(nPn);                           /* Compute the function value */
    nYn1 = fFunction(nPn1);                          /* Compute the function value */
    if(nPrint)
    {
        printf("\n\n    N    %-10s   %-10s   %-10s   %-10s   %-10s  "
               ,"Pn","Pn+1","Pn+2","Ek+1","Ek+2");
        printf("\n------------------------------------------------------------------");
    }
    for(i = 1; i <= nMaxIter && nRet == -1 ; i++)
    {
        /* Compute the slope */
        nDf = (nYn1 - nYn)/(nPn1 - nPn);
        if(nDf == 0)
        {
            nRet = -2;   nDp  = 0; /* Divide error */
        }
        else
        {
            nDp = nYn1/nDf;    
        }

        nPn2  = nPn1 - nDp;   nYn2  = fFunction(nPn2);
        if(nPrint)
            printf("\n   %2d  %2.8lf  %2.8lf  %2.8lf  %2.8lf  %2.8lf  "
                   ,i-1,nPn,nPn1,nPn2,nPn1 - nPn,nPn2 - nPn1);
         nRelErr = 2 * fabs(nDp)/(fabs(nPn2) + nSmall);
        if(nRelErr < nDelta && fabs(nYn2) < nEpsilon)
        {
            if(nRet != -2)
            {
                /* Convergence has been found on the given tolerance */
                nRet = 0;  
                *pOutput = nPn2;  *pDp     = nDp;
            }
        }
        nPn  = nPn1;  nPn1 = nPn2;   nYn  = nYn1; nYn1 = nYn2;
    }
    if(nPrint)
        printf("\n------------------------------------------------------------------");
    return nRet;
}
