#include "NonLinearFunc.h"
#include "LSLineFunc.h"

/* Function name       : computeNonlinearCurve
* Description         : Computes a non-linear curv using data linearization.
* Parameter(s)        : 
*     nForm              [in]  The form of non-linear equation.
*     *pXPoints          [in]  The X coordinate vector.
*     *pYPoints          [in]  The Y coordinate vector corresponding to each point in X.
*     nNumPoints         [in]  The number of elements or data points.
*     pA                 [out] The A coefficient.
*     pB                 [out] The B coefficient.
*     pC                 [out] The C coefficient.
*     pD                 [out] The D coefficient.
* Return              :     
*    int _cdecl       0  - Success
*                    -1  - Insufficient data points.
*                    -2  - Invalid nonlinear form.
*/
int  _cdecl
computeNonlinearCurve(int nForm,double *pXPoints,double *pYPoints,int nNumPoints,double* pA,double* pB,double* pC,double* pD)
{
    int nRet = 0;
    int i;
    *pA = 0,  *pB = 0, *pC = 0, *pD = 0;
    switch(nForm)
    {
    case 0:
        /* Convert the Xj = 1/xj, Yj = yj; */
        for(i = 0; i < nNumPoints; i++)
        {
            pXPoints[i] = 1 / pXPoints[i];
            /* pYPoints[i] = pYPoints[i]; */
        }
        break;
    case 1:
        /* Convert the Xj = xjyj, Yj = yj; */
        for(i = 0; i < nNumPoints; i++)
        {
            pXPoints[i] = pXPoints[i] * pYPoints[i];
            /* pYPoints[i] = pYPoints[i]; */
        }
        break;
    case 2:
        /* Convert the Xj = xj, Yj = 1/yj; */
        for(i = 0; i < nNumPoints; i++)
        {
            /* pXPoints[i] = pXPoints[i]; */
            pYPoints[i] = 1 / pYPoints[i]; 
        }
        break;
    case 3:
        /* Convert the Xj = 1/xj, Yj = 1/yj; */
        for(i = 0; i < nNumPoints; i++)
        {
            pXPoints[i] = 1 / pXPoints[i]; 
            pYPoints[i] = 1 / pYPoints[i]; 
        }
        break;
    case 4:
        /* Convert the Xj = ln(xj), Yj = yj; */
        for(i = 0; i < nNumPoints; i++)
        {
            pXPoints[i] = log(pXPoints[i]); 
           /* pYPoints[i] = pYPoints[i]; */
        }
        break;
    case 5:
        /* Convert the Xj = xj, Yj = ln(yj); */
        for(i = 0; i < nNumPoints; i++)
        {
            /* pXPoints[i] = pXPoints[i]; */ 
             pYPoints[i] = log(pYPoints[i]); 
        }
        break;
    case 6:
        /* Convert the Xj = ln(xj), Yj = ln(yj); */
        for(i = 0; i < nNumPoints; i++)
        {
             pXPoints[i] = log(pXPoints[i]);
             pYPoints[i] = log(pYPoints[i]); 
        }
        break;
    case 7:
        /* Convert the Xj = xj, Yj = (yj)^0.5; */
        for(i = 0; i < nNumPoints; i++)
        {
             /*pXPoints[i] = pXPoints[i]; */
             pYPoints[i] = 1 / sqrt(pYPoints[i]); 
        }
        break;
    default:
        /* Invalid form */
        nRet = -2;
        break;
    }


    if(nRet == 0)
        /* Compute the linearized data */
        nRet = computeLSLine(pXPoints,pYPoints,nNumPoints,pA,pB);

    if(nRet == 0)
    {
        switch(nForm)
        {
        case 1:
            /* C = -1/A, D = -B/A */
            *pC = -1 / (*pA);
            *pD = -1 * (*pB) / (*pA);
            break;
        case 5:
        case 6:
            /* C = exp(B) */
            *pC  = exp(*pB);
            break;
        default:
            break;
        }
    }

    return nRet;
}

