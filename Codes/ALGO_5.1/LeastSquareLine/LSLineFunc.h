#ifndef LSLineFunc_h
#define LSLineFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int _cdecl computeLSLine(double *pXPoints,double *pYPoints,int nNumPoints,double* pA,double* pB);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
