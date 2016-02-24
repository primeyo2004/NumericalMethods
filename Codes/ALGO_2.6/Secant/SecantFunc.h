#ifndef SecantFunc_h
#define SecantFunc_h

#include <math.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


int _cdecl computeSecant(double nPn,double nPn1,double (*fFunction)(double),int nMaxIter,int nPrint,double *pOutput,double *pDp,int* pIterCnt);


#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif

