#ifndef MilneSimpsonFunc_h
#define MilneSimpsonFunc_h

#include  <math.h>
#include  <stdio.h>
#include  <memory.h>
#include  <malloc.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


int _cdecl computeMilneSimpson(double nLowerLimit,double nUpperLimit,double nInitYValue[],int nInterval,double (*pFuncOfTY)(double,double),double *pTPoints,double *pYPoints);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif




