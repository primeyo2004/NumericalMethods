#ifndef NonLinearFunc_h
#define NonLinearFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int  _cdecl computeNonlinearCurve(int nForm,double *pXPoints,double *pYPoints,int nNumPoints,double* pA,double* pB,double* pC,double* pD);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
