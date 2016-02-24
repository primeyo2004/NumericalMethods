#ifndef FixedPointFunc_h
#define FixedPointFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int _cdecl computeFixedPoint(double nPterm,double (*gFunction)(double),int nMaxIter,double largeVal,int nPrint,double *pOutput,double *pDelta);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

