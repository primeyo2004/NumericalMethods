#ifndef JacobiFunc_h
#define JacobiFunc_h

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

int  __cdecl computeJacobi(double  *pMatrix,int nSize,double* pInputB,double* pOuputX,int nMaxIter,int* pnActualIter,int nDispIter);



#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
