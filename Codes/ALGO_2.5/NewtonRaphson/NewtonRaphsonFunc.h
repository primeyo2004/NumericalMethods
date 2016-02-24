#ifndef NewtonRaphsonFunc_h
#define NewtonRaphsonFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


int _cdecl 
computeNewtonRaphson(double nPn,double (*fFunction)(double),double (*fFunction1)(double),int nMaxIter,int nPrint,double *pOutput,double *pDp,int* pIterCnt);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

