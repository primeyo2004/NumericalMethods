
#ifndef UpperTriangle_h
#define UpperTriangle_h

#include <math.h>
#include <memory.h>
#include <malloc.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#if !(defined MATRIXE)
	#define      MATRIXE(Matrix,i,j,nColWidth)      *((Matrix) + ((i) * (nColWidth)) + (j))
#endif

int __cdecl upperTriangleAndBackSub(double  *pAugmentedMatrix,int nSize,double *pOutputVector);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
