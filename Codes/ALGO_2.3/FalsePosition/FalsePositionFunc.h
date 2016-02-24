#ifndef FalsePositionFunc_h
#define FalsePositionFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define    GETSIGN(x)         (((x) < 0) ? -1:(((x) == 0) ? 0:1)) /* return -1 if negative, 0 if 0, 1 if pos */

int _cdecl computeFalsePosition(double nA,double nB,double (*fFunction)(double),int nMaxIter,int nPrint,double *pOutput,double* pDx);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

