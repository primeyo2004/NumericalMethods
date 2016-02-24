
#ifndef LUFactoring_h
#define LUFactoring_h

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

int __cdecl constructLUP(double  *pAugmentedMatrix,int nSize,int *pPermVect,double* pDeterminant);

int  __cdecl computeXfromULP(double  *pMatrix,int nSize,int *pPvtRowVect,double* pInputB,double* pOuputX);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
