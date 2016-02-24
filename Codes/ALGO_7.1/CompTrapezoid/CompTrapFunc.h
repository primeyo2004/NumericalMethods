#ifndef CompTrapFunc_h
#define CompTrapFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int _cdecl computeCompTrapezoidal(double nLowerLimit,double nUpperLimit,int nInterval, double (*funcOfX)(double nX),double *pResult);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif
