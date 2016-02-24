#include "CrankHeatFunc.h"

#define  MAX_VECT_SIZE  51

int 
tridiagonal(double a[],double d[],double c[],double x[],double b[],int n);

/* Function name      : computeCrankHeat
* Description         : Computes the Crank-Nicholson's method for the Heat Equation.
* Parameter(s)        : 
*     wid_A         [in]  The width  of the rectangular grid.
*     ht_B          [in]  The height of the rectangular grid.
*     cons_C        [in]  constant of heat eq.. 
*     cons_C1       [in]  constant cons_C1 = u(0,t). 
*     cons_C2       [in]  constant cons_C2 = u(wid_A,t).
*     xdim_N        [in]  The dimension in X.
*     ydim_M        [in]  The dimension in Y.
*     pFFunc        [in]  f(x)
*     gridU         [out] The grid.
*     maxWid         [in]  The max width of the grid.
* Return              :     
*    0   - Success
*/
int     
computeCrankHeat(double wid_A,double ht_B,double cons_C,double cons_C1,double cons_C2,int xdim_N,int ydim_M,double(*pFFunc)(int,double),double* gridU,int maxWid)
{
    int nRet = 0;

    double    dx_H;       /* The delta X */
    double    dy_K;       /* The delta Y */ 
    double    ratio_R;    /* The  ratio ratio_R */
    double    term_S1;     /* 2 + 2/ratio_R */
	double    term_S2;     /* 2/ratio_R - 2*/

	double VectA[MAX_VECT_SIZE], VectB[MAX_VECT_SIZE]; /* diagonal and off-diagonal             */
    double VectC[MAX_VECT_SIZE], VectD[MAX_VECT_SIZE]; /* elements of matrix A (see book)       */
    double A0[MAX_VECT_SIZE], B0[MAX_VECT_SIZE]; /* backup of the VectA, VectB, VectC    */
    double C0[MAX_VECT_SIZE], D0[MAX_VECT_SIZE]; /* and VectD                                */
    double X0[MAX_VECT_SIZE];          /* Solution vector for tridiagonal syst. */
    
    int i,j;

    /* Compute step sizes */
    dx_H  = wid_A / ( xdim_N - 1 );
	dy_K  = ht_B / ( ydim_M - 1 );

    /* Compute ratios and constants */
    ratio_R  = cons_C * cons_C * dy_K / ( dx_H * dx_H );
    term_S1 = 2.0 + 2.0 / ratio_R;
    term_S2 = 2.0 / ratio_R  - 2.0;

	for ( i = 0; i < xdim_N; i++ ) GRID(gridU,i,0,maxWid) = 0.0;
    for ( i = 1; i < ydim_M; i++ ) GRID(gridU,0,i,maxWid) = 0.0;

    /* Boundary conditions */
    for ( j = 1; j <= ydim_M; j++ ) 
    {
           GRID(gridU,1,j,maxWid) = cons_C1;
           GRID(gridU,xdim_N,j,maxWid) = cons_C2;
    }

    /* First row  */
    for ( i = 2; i <= xdim_N - 1 ; i++ ) GRID(gridU,i,1,maxWid) = pFFunc(i,dx_H);

    /* Form the diagonal elements of the matrix wid_A */
    for ( i = 1; i <= xdim_N ; i++ ) VectD[i] = term_S1;
    VectD[1] = 1.0;
    VectD[xdim_N] = 1.0;

    /* Form the off diagonal Elements of the matrix wid_A */

    for ( i = 1; i <= xdim_N - 1 ; i++ ) 
    {
        VectA[i] = -1.0;
        VectC[i] = -1.0;
    }
       
    VectA[xdim_N-1] = 0.0;
    VectC[1]   = 0.0;

    VectB[1] = cons_C1;
    VectB[xdim_N] = cons_C2;

    /* Construct successive rows in the grid */

    for ( j = 2; j <= ydim_M; j++ )
    {
        for ( i = 2; i <= xdim_N - 1; i++ ) 
        {
            VectB[i] = GRID(gridU,i-1,j-1,maxWid) + GRID(gridU,i+1,j-1,maxWid) + term_S2 * GRID(gridU,i,j-1,maxWid);
        }

        /* Make a copy of the vetor since it will be 
		   modified by triSytem
		*/
        for ( i = 1; i <= xdim_N; i++ ) 
        {
            A0[i] = VectA[i];
            B0[i] = VectB[i];
            C0[i] = VectC[i];
            D0[i] = VectD[i];
        }


		/* Solve the tri diagonal-system */
		tridiagonal(A0,D0,C0,X0,B0,xdim_N);
		
		/* Next row in grid */

        for ( i = 1; i <= xdim_N; i++ ) GRID(gridU,i,j,maxWid) = X0[i];

    } /* End of outer for-loop*/

 
    return nRet;
}


/* Function name       : triadiagonal
* Description         : Solves the triadiagonal system
* Parameter(s)        : 
*	 a[]		 [in]   The sub diagonal vector.
*	 d[]		 [in]   The diagonal vector.
*	 c[]		 [in]   The super diagonal vector.
*	 x[]		 [out]  The unknown vector.
*	 b[]		 [in]   The constant vector.
*	 n		     [in]   The number of elements.
* Return              :     
*    int  0 - Success.
*        -1 - Failed. 
*                 
*--------------------------------------------------------------------------------*/
int 
tridiagonal(double a[],double d[],double c[],double x[],double b[],int n)
{
	int nRet = 0;

	int k;

	for(k = 2; k <= n; k++)
	{
		if(!d[k-1])
		{
			/* Signal failure and stop */
			nRet = -1;
			break;
		}
		else
		{
			double m;

			m = a[k-1]/d[k-1];

			d[k] = d[k] - m*c[k-1];
			b[k] = b[k] - m*b[k-1];
		}
	}

	if(nRet == 0)
	{
		if(!d[n])
		{
			/* Signal failure and stop */
			nRet = -1;
		}
		else
		{
			x[n] = b[n]/d[n];

			for(k = n-1; k >= 1; k--)
			{
				x[k] = (b[k] - c[k] * x[k+1]) / d[k];
			}

		}
	}
	
	return nRet;
}