#ifndef CompSimpFunc_h
#define CompSimpFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int _cdecl computeCompSimpson(double nLowerLimit,double nUpperLimit,int nInterval, double (*funcOfX)(double nX),double *pResult);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
