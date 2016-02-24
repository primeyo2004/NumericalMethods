#include "ForwardiffFuncH.h"

/* Function name      : computeForwardDiffHeat
* Description         : Computes the Forward-Difference for the Heat Equation.
* Parameter(s)        : 
*     wid_A         [in]  The width  of the rectangular grid.
*     ht_B          [in]  The height of the rectangular grid.
*     cons_C        [in]  constant of heat eq.. 
*     cons_C1       [in]  constant C1 = u(0,t). 
*     cons_C2       [in]  constant C2 = u(A,t).
*     xdim_N        [in]  The dimension in X.
*     ydim_M        [in]  The dimension in Y.
*     pFFunc        [in]  f(x)
*     gridU         [out] The grid.
*     maxWid         [in]  The max width of the grid.
* Return              :     
*    0   - Success
*/
int     
computeForwardDiffHeat(double wid_A,double ht_B,double cons_C,double cons_C1,double cons_C2,int xdim_N,int ydim_M,double(*pFFunc)(int,double),double* gridU,int maxWid)
{
    int nRet = 0;

    double    dx_H;       /* The delta X */
    double    dy_K;       /* The delta Y */ 
    double    ratio_R;    /* The  ratio R */
    double    term_S;     /* 1 - 2*R */
    
    int i,j;
  
    /* Compute step sizes */
    dx_H   = wid_A / ( xdim_N - 1 );
    dy_K   = ht_B / ( ydim_M - 1 );
    ratio_R   = cons_C * cons_C * dy_K / ( dx_H * dx_H );
    term_S   = 1.0 - 2.0 * ratio_R;

    /* Assign boundary conditions */
    for ( j = 1; j <= ydim_M; j++ )
    {
        GRID(gridU,1,j,maxWid) = cons_C1;
        GRID(gridU,xdim_N,j,maxWid) = cons_C2;
    }

    /* Fill the first row */
    for ( i = 2; i <= xdim_N - 1 ; i++ ) GRID(gridU,i,1,maxWid) = pFFunc(i,dx_H);

    /* Generate new waves */
    for ( j = 2; j <= ydim_M; j++ )
    {
        for ( i = 2; i <= xdim_N - 1; i++ )
        {
            GRID(gridU,i,j,maxWid) = term_S * GRID(gridU,i,j-1,maxWid) + ratio_R * ( GRID(gridU,i-1,j-1,maxWid) + GRID(gridU,i+1,j-1,maxWid) );
        }
    }
 
    return nRet;
}