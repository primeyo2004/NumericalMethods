#ifndef BisectionFunc_h
#define BisectionFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define    GETSIGN(x)         (((x) < 0) ? -1:(((x) == 0) ? 0:1)) /* return -1 if negative, 0 if 0, 1 if pos */

int _cdecl computeBisection(double nA,double nB,double (*fFunction)(double),int nPrint,double *pOutput,double* pAccuracy);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

