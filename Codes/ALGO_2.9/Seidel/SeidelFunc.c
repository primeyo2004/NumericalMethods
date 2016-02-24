#include "SeidelFunc.h"

/* Function name       : computeSeidel
* Description          : Computes the roots of the system using seidel iteration.
* Parameter(s)        : 
*     nPn         [in]  Initial value P0.
*     nQn         [in]  Initial value Q0.
*     gFunc1      [in]  g1(x,y)
*     gFunc2      [in]  g2(x,y)
*     nMaxIter    [in]  The maximum number of iteration.
*    nPrint       [in]  Flag for printing the output on screen,
*     *pX         [out]  The X root.
*     *pY         [out]  The Y root.
*     pIterCnt    [out]  The number of iterations taken.
* Return              :     
*    int   0 - Success, -1 - The iteration didn't converge.
*/
int _cdecl 
computeSeidel(double nPn,double nQn,FuncXY gFunc1,FuncXY gFunc2,int nMaxIter,int nPrint,double *pX,double *pY,int* pIterCnt)
{
    int nRet = 0;                                 

    static const double nTol      = 10e-8;        /* Tolerance*/
    double nSep = 1;                              /* Total relative errors */
    double nPn1;                                  /* Pn+1  */
    double nQn1;                                  /* Qn+1  */
    int    i;
        
    if(nPrint)
    {
        printf("\n\n    N    %-10s   %-10s  ","Pn","Qn");
        printf("\n------------------------------------------------------------------");
        printf("\n   %2d  %2.8lf  %2.8lf  ",0,nPn,nQn);
    }
    i = 0;
    while(i < nMaxIter && nSep > nTol)
    {
        i++;

        nPn1 = gFunc1(nPn,nQn); nQn1 = gFunc2(nPn1,nQn);

        if(nPrint)
            printf("\n   %2d  %2.8lf  %2.8lf  ",i,nPn1,nQn1);

        nSep = fabs(nPn1 - nPn) + fabs(nQn1 - nQn) ;

        nPn = nPn1;    nQn = nQn1;
    }

    if(nSep < nTol)
    {
        nRet = 0;

        *pX = nPn;
        *pY = nQn;
    
        *pIterCnt = i;

    }
    else
    {
        nRet = -1;
    }

    if(nPrint)
        printf("\n------------------------------------------------------------------");

    return nRet;
}

