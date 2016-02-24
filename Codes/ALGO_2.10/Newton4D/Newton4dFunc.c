#include "Newton4dFunc.h"
#include "UpperTriangle.h"


/*Function name       : computeNewton4D
* Description         : Computes a 4 dimesional non-linear system using Newton-Raphson
* Parameter(s)        : 
*     nPnVect          [in]  The input vector nPnVect[0],nPnVect[1],nPnVect[2],nPnVect[3]
*     *pAugFuncMatrix  [in]  The Augmented matrix of function pointers.
*     nMaxIter         [in]  The maximum number of iterations.
*     nPrint           [in]  Flag for printing the output on screen,
*     nPnOutVect       [out] Output vector.
*     pIterCnt         [out] Number of iterations taken.
* Return              :     
*    int   0 - Sucess, -1 - Mem error, -2 - Singular matrix, -3 - Iteration exceeded.
*/
int _cdecl computeNewton4D(double* nPnVect,Func4 *pAugFuncMatrix,int nMaxIter,int nPrint,double* nPnOutVect,int* pIterCnt)
{
    int nRet = 0;
    int nDone = 0;
    static const  double  nDelta   = 10e-8;
    static const  double  nEpsilon = 10e-8;
    static const  double  nSmall   = 10e-8;
    double nRelError = 0;
    double  nPnOp[4];                 /* The duplicate value of P */
    double  nPn1Op[4];                /* Pn+1 */
    double  deltaPVector[4];          /* The Change in P vetor */
    double  augOprMtrx[4][5];         /* Matrix used for the computation */    
    double  *pAugOpMatrix = NULL;
    Func4   pFuncCurrent  = NULL;      /* Pointer to the current function */
    int   k;
    int   i,j;
    /* init the operation */
    nPnOp[0] = nPnVect[0];
    nPnOp[1] = nPnVect[1];
    nPnOp[2] = nPnVect[2];
    nPnOp[3] = nPnVect[3];
    if(nPrint)
    {
        printf("\n\n    N    %-10s   %-10s  %-10s   %-10s   ","P0n","P1n","P2n","P3n");
        printf("\n------------------------------------------------------------------");
        printf("\n   %2d  %2.8lf  %2.8lf  %2.8lf  %2.8lf  "
               ,0,nPnOp[0],nPnOp[1],nPnOp[2],nPnOp[3]);
    }
    /* use the pointer version */
    pAugOpMatrix = &augOprMtrx[0][0];
    for(k = 1; k <= nMaxIter && nRet == 0 && nDone == 0; k++)
    {
        /* Assuming that pAugFuncMatrix is a 4x5 Augmented matrix */
        /* Get the results of the partial function derivatives */
        /* a[i,j] = df[i,j] (x0,x1,x2,x3); */
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                pFuncCurrent = MATRIXE(pAugFuncMatrix,i,j,5);
                MATRIXE(pAugOpMatrix,i,j,5) = 
                    pFuncCurrent(nPnOp[0],nPnOp[1],nPnOp[2],nPnOp[3]);
            }
        }

        /* Compute the Augmented vector F(x0,x1,x2,x3) */
        for(i = 0; i < 4; i++)
        {
            pFuncCurrent = MATRIXE(pAugFuncMatrix,i,4,5);
            MATRIXE(pAugOpMatrix,i,4,5) 
                = -1 * pFuncCurrent(nPnOp[0],nPnOp[1],nPnOp[2],nPnOp[3]);
        }
        /* Use Linear systems operations */
        nRet = upperTriangleAndBackSub(pAugOpMatrix,4,deltaPVector);
        if(nRet == 0)
        {
            double nSumDelta = 0;
            double nSumPn1   = 0;
            double nSumFunc  = 0;
            for(j=0; j < 4; j++)
            {
                /* Get the new value */
                nPn1Op[j] = nPnOp[j] + deltaPVector[j];
                nSumDelta += fabs(deltaPVector[j]);
                nSumPn1   += fabs(nPn1Op[j]);
            }
            for(i = 0; i < 4; i++)
            {
                /* Get the  - fj(x0,x1,x2,x3) */
                pFuncCurrent = MATRIXE(pAugFuncMatrix,i,4,5);
                nSumFunc +=  fabs(pFuncCurrent(nPn1Op[0],nPn1Op[1],nPn1Op[2],nPn1Op[3]));
            }

            nSumPn1   += nSmall;
            /* Compute the relative error */
            nRelError = nSumDelta/nSumPn1;
            if(nRelError < nDelta && nSumFunc < nEpsilon)
                nDone = 1;

            /* Transfer the Values */
            for(j=0; j < 4; j++)
                nPnOp[j] = nPn1Op[j];
            if(nPrint)
                printf("\n   %2d  %2.8lf  %2.8lf  %2.8lf  %2.8lf  ",k,nPnOp[0],nPnOp[1],nPnOp[2],nPnOp[3]);
        }
    }

    if(nRet == 0)
    {
        /* iteration exceeded */
        if(nDone == 0)
            nRet = -3;

        for(j=0; j < 4; j++)
            /* Copy it to the output */
            nPnOutVect[j] = nPnOp[j];

        *pIterCnt = k;
    }

    if(nPrint)
        printf("\n------------------------------------------------------------------");

    return nRet;
}