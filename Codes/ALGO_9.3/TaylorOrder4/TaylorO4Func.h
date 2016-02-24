#ifndef TaylorO4Func_h
#define TaylorO4Func_h

#include  <math.h>
#include  <stdio.h>
#include  <memory.h>
#include  <malloc.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef  double (*FuncTY)(double nT,double nY);

int _cdecl computeTaylorO4(double nLowerLimit,double nUpperLimit,double nInitYValue,int nInterval,FuncTY funcOfTY[],double *pTPoints,double *pYPoints);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif




