#include "FiniteDiffFuncW.h"

/* Function name      : computeFiniteDiffWave
* Description         : Computes the Finite-Difference of the Wave Equation.
* Parameter(s)        : 
*     wid_A          [in]  The width  of the rectangular grid.
*     ht_B           [in]  The height of the rectangular grid.
*     cons_C         [in]  The constant  of wave eq.. 
*     xdim_N         [in]  The dimension in X.
*     ydim_M         [in]  The dimension in Y.
*     pGFunc      [in]  g(x)
*     pFFunc      [in]  f(x)
*     gridU         [out] The grid.
*     maxWid         [in]  The max width of the grid.
* Return              :     
*    0   - Success
*/
int     
computeFiniteDiffWave(double wid_A,double ht_B,double cons_C,int xdim_N,int ydim_M,double(*pGFunc)(int,double),double(*pFFunc)(int,double),double* gridU,int maxWid)
{
    int nRet = 0;

    double    dx_H;       /* The delta X */
    double    dy_K;       /* The delta Y */ 
    double    ratio_R;    /* The  ratio R */
    double    ratio_R2;   /* R^2   */
    double    ratio_R22;  /* R^2/2 */
    double    term_S1;    /* 1 - R^2 */
    double    term_S2;    /* 2 - 2R^2 */
    int i,j;
  
    /* Compute step sizes */
    dx_H      = wid_A / (xdim_N - 1);  
    dy_K      = ht_B / ( ydim_M - 1 );
    ratio_R   = cons_C * dy_K / dx_H;   
    ratio_R2  = ratio_R * ratio_R; 
    ratio_R22 = ratio_R * ratio_R / 2.0;
    term_S1   = 1.0 - ratio_R * ratio_R;
    term_S2   = 2.0 - 2.0 * ratio_R * ratio_R;

    /* Apply boundary conditions */
    for ( j = 1; j <= ydim_M; j++ )
    {
        GRID(gridU,1,j,maxWid)      = 0;
        GRID(gridU,xdim_N,j,maxWid) = 0;
    }
    /* Compute the starting values: first and second rows */
    for ( i = 2; i <= xdim_N - 1 ; i++ ) 
    {
        GRID(gridU,i,1,maxWid) = pFFunc(i,dx_H);
        GRID(gridU,i,2,maxWid) = term_S1 * pFFunc(i,dx_H) + dy_K * pGFunc(i,dx_H) + ratio_R22 * ( pFFunc(i+1,dx_H) + pFFunc(i-1,dx_H));
    }

    /* Generate new waves */
    for ( j = 3; j <= ydim_M; j++ )
    {
        for ( i = 2; i <= xdim_N - 1; i++ )
        {
            GRID(gridU,i,j,maxWid) = term_S2 * GRID(gridU,i,j-1,maxWid) + ratio_R2 
                * ( GRID(gridU,i-1,j-1,maxWid) + GRID(gridU,i+1,j-1,maxWid)) - GRID(gridU,i,j-2,maxWid);
        }
    }
 
    return nRet;
}