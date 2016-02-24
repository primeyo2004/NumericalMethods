#ifndef LSPolyFunc_h
#define LSPolyFunc_h

#include <math.h>
#include <malloc.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int _cdecl computeLSPoly(double *pXPoints,double *pYPoints,int nNumPoints,int nDegree,double* pCoefficients);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
