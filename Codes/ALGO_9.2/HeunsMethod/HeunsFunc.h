#ifndef HeunsFunc_h
#define HeunsFunc_h

#include  <math.h>
#include  <stdio.h>
#include  <memory.h>
#include  <malloc.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int _cdecl computeHeunsMethod(double nLowerLimit,double nUpperLimit,double nInitYValue,int nInterval,double (*pFuncOfTY)(double t,double y),double *pTPoints,double *pYPoints);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif




