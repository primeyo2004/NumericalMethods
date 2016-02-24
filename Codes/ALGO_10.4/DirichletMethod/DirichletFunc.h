
#ifndef DirichletFunc_h
#define DirichletFunc_h

#include <math.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if !(defined GRID)
	/*This grid accepts a one based input */
	#define      GRID(gridU,i,j,nColWidth)      *((gridU) + (((i)-1) * (nColWidth)) + ((j)-1))
#endif

typedef  double (*FUNCF )(int,double); 

int     
computeDirichlet(double wid_A,double ht_B,double space_H,int xdim_N,int ydim_M,double initVal,FUNCF arrFunc[],double* gridU,int maxWid);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif  