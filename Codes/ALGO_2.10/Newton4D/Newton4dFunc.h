#ifndef Newton4dFunc_h
#define Newton4dFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef   double (*Func4)(double x0,double x1,double x2,double x3);

int _cdecl computeNewton4D(double* nPnVect,Func4 *pFuncMatrix,int nMaxIter,int nPrint,double* nPnOutVect,int* pIterCnt);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

