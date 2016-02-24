#ifndef SeidelFunc_h
#define SeidelFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef   double (*FuncXY)(double x,double y);

int _cdecl computeSeidel(double nPn,double nQn,FuncXY gFunc1,FuncXY gFunc2,int nMaxIter,int nPrint,double *pX,double *pY,int* pIterCnt);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

