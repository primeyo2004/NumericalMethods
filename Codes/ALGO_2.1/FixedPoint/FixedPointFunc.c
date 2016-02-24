#include "FixedPointFunc.h"

/* Function name      : computeFixedPoint
* Description         : Computes the x = g(x) using  the Fixed-Point iteration.
* Parameter(s)        : 
*     nPterm           [in]  The initial value.
*     gFunction        [in]  The function that will evaluate the g(x)
*     nMaxIter         [in]  The maximum number of iterations.
*     largeVal         [in]  The absolute value used as boundary for the iteration.
*     nPrint           [in]  Flag for printing the output on screen,
*     *pOutput         [out]  The Fixed-Point output.
*     *pDelta          [out]  The relative error  |Pn+1 - Pn|
* Return              :     
*    int       -  0  Converging,  -  -1  Diverging.
*/
int _cdecl 
computeFixedPoint(double nPterm,double (*gFunction)(double),int nMaxIter,double largeVal,int nPrint,double *pOutput,double *pDelta)
{
    int nRet = 0;
    static const double nTolerance  = 10e-8; /* The stopping point tolerance */
    static const double nMinDivisor = 10e-8; /* The minimum divisor */
    int      i;
    double   nRelError  = 1;  /* program relative error  
                               Note: the real relative error is g(Pn+1) - g(Pn) */            
    double   nPnew;           /* the new value */              
    double   nPold;           /* the current value */
    double   nDg;             /* The difference between g(Pn+1) - g(Pn)  */ 
    double   nDx;             /* The difference between Pn+1 - Pn        */ 
    double   nSlope;          /* The slope of the secant (Pn,g(pn)) (Pn+1,g(Pn+1))*/ 
	/* Init values */
    *pOutput = 0; *pDelta  = 0;
    nPnew    = gFunction(nPterm);
    nDg = nPnew - nPterm;
    i = 0;
    if(nPrint)
    {
        printf("\n N \t %-13s \t %-13s \t %-13s ","Pn","Pn+1","Relative Error");
        printf("\n-------------------------------------------------------");
        printf("\n %02d \t %5.8lf \t %5.8lf \t %2.8lf ",i,nPterm,nPnew,fabs(nDg));
    }
    /* This has been slightly modified to save some variables 
       result is still the same.
    */
    while(nRelError >= nTolerance 
		  && i < nMaxIter 
		  && largeVal > fabs(nPnew))
    {
        i++;
        nPold  = nPterm;
        nPterm = nPnew;
        /* compute the Pn+1 */
        nPnew = gFunction(nPterm);
        nDg = nPnew - nPterm;
        nRelError = 2 * fabs(nDg) / (fabs(nPnew) + nMinDivisor);
        if(nPrint)
            printf("\n %02d \t %5.8lf \t %5.8lf \t %2.8lf ",i,nPterm,nPnew,fabs(nDg));
    }

    nDx    = nPterm - nPold;
    nSlope = nDg / (nDx + nMinDivisor);
    *pOutput = nPnew;
    /* This is the real relative error is g(Pn+1) - g(Pn) */
    *pDelta  = fabs(nDg);
    if(fabs(nSlope) > 1)
        nRet = -1;
    if(nPrint)
        printf("\n-------------------------------------------------------");
    return nRet;
}

