
#ifndef ForwardiffFuncH_h
#define ForwardiffFuncH_h

#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if !(defined GRID)
	/*This grid accepts a one based input */
	#define      GRID(gridU,i,j,nColWidth)      *((gridU) + (((i)-1) * (nColWidth)) + ((j)-1))
#endif

int     
computeForwardDiffHeat(double wid_A,double ht_B,double cons_C,double cons_C1,double cons_C2,int xdim_N,int ydim_M,double(*pFFunc)(int,double),double* gridU,int maxWid);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  