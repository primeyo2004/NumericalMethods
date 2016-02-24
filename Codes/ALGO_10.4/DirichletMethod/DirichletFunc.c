#include "DirichletFunc.h"

/* Function name      : computeDirichlet
* Description         : Computes the Dirichlet's method for Laplace's Equation.
* Parameter(s)        : 
*     wid_A         [in]  The width  of the rectangular grid. (This is not used.)
*     ht_B          [in]  The height of the rectangular grid. (This is not used.)
*	  space_H		[in]  The grid spacing for x & y.
*     xdim_N        [in]  The dimension in X.
*     ydim_M        [in]  The dimension in Y.
*	  initVal		[in]  The initial value for ui,j.
*     arrFunc       [in]  Array of functions containing f1(i,H),f2(i,H),f3(i,H),f3(i,H)
*     gridU         [out] The grid.
*     maxWid        [in]  The max width of the grid.
* Return              :     
*    0   - Success
*/
int     
computeDirichlet(double wid_A,double ht_B,double space_H,int xdim_N,int ydim_M,double initVal,FUNCF arrFunc[],double* gridU,int maxWid)
{
    int nRet = 0;
    
    int i,j;

	const static double PI = 3.1415926535897932384626433832795;
	double   temp;
	double   w;
	double   Relax;
	double   nTol;    /* Iteration tolerance */
	int      nCount;  /* Iteration counter */

    /* Initialize starting values at the interior points */
    for ( i = 2; i <= xdim_N-1; i++ )
    {
        for ( j = 2; j <= ydim_M-1; j++ )   GRID(gridU,i,j,maxWid) = initVal;
    }

    /* Store boundary values in the solution matrix */
    for ( j = 1; j <= ydim_M ; j++ ) 
    {
        GRID(gridU,1,j,maxWid) = arrFunc[2](j,space_H);
        GRID(gridU,xdim_N,j,maxWid) = arrFunc[3](j,space_H);
    }

    for ( i = 1; i <= xdim_N ; i++ ) 
    {
        GRID(gridU,i,1,maxWid) = arrFunc[0](i,space_H);
        GRID(gridU,i,ydim_M,maxWid) = arrFunc[1](i,space_H);
    }

    /* The SQR parameter */
    temp =  cos( PI/(xdim_N-1) ) + cos( PI/(ydim_M-1) );

    w = 4.0 / ( 2.0 + sqrt( 4.0 - temp * temp ) );

    /* Initialize the loop control parameters */

    nTol   = 1.0;
    nCount = 0;

    while ( (nTol > 0.001) && (nCount <= 140) )
    {
       nTol = 0.0;
       for ( j = 2; j <= ydim_M - 1; j++ )
       {
           for ( i = 2; i <= xdim_N - 1; i++ )
           {
             Relax = w * ( GRID(gridU,i,j+1,maxWid) + GRID(gridU,i,j-1,maxWid) + GRID(gridU,i+1,j,maxWid) +
                           GRID(gridU,i-1,j,maxWid) - 4.0 * GRID(gridU,i,j,maxWid) ) / 4.0;
             GRID(gridU,i,j,maxWid) += Relax;
             if( fabs(Relax) > nTol ) nTol = fabs(Relax);
           }
       }

	   nCount++;
    }
 
    return nRet;
}

