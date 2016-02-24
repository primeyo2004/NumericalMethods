#include "GaussSeidelFunc.h"

/* Function name       : computeGaussSeidel
* Description         : Solves linear systems using the Gauss - Seidel iteration.
* Parameter(s)        : 
*     *pMatrix         [in]  The coeffecient n x n Matrix.
*     nSize            [in]  The dimension of matrix.
*     pInputB          [in]  The constants.
*     pOuputX          [out] The unknown vectors.
*     nMaxIter         [in]  The maximum number of iteration.
*     pnActualIter     [out] The actual iteration taken until the system is solved.
*     nDispIter        [in]  If non-0 the vectors values in each iteration will be displayed.
*                       
* Return              :     
*    int  
*              0   - Success, -1   - Memory allocation error, 
*             -2   - Not diagonally dominant, -3   - Solution didn't converge
*/
int  __cdecl 
computeGaussSeidel(double  *pMatrix,int nSize,double* pInputB,double* pOuputX,int nMaxIter,int* pnActualIter,int nDispIter)
{
    int nRet = 0;
    double *pOuputXNew = NULL;
    double  nTol  = 10e-8;    /* The tolerance convergence */
    double  nDiff = 1;        /* The summation of difference between 
                                the old values and new values */
    int     nIdx;
    *pnActualIter = nMaxIter;
    /* Check of the diagonal domimance */
    for(nIdx = 0; nIdx < nSize; nIdx++)
    {
        double nSumRow = 0;
        int  nCol;
        for(nCol = 0; nCol < nSize; nCol++)
            nSumRow += fabs(MATRIXE(pMatrix,nIdx,nCol,nSize));
        if(nSumRow >= fabs(MATRIXE(pMatrix,nIdx,nIdx,nSize)) * 2)
        {   /* Not diagonally dominant */
            nRet = -2;
            break;
        }
    }
    if(nRet == 0)
    {   /* Allocate memory for new output values */
        pOuputXNew = (double*) malloc(nSize * sizeof(double));
        if(!pOuputXNew)  nRet = -1;
    }

    if(nRet == 0)
    {
        int  nIterCtr = 1;
        /* Initialize the output */
        for(nIdx = 0; nIdx < nSize; nIdx++)
        {
            pOuputX[nIdx] = 0;
            /* Display iteration values */
            if(nDispIter)
            {
                if(nIdx)
                    printf(" %2.7lf ",pOuputX[nIdx]);
                else
                {
                    int i;
                    printf("\n   N   ");
                    for(i = 0; i < nSize; i++)  printf("  X(%02d)    ",i);
                    printf("\n (%02d) ",0);
                    printf(" %2.7lf ",pOuputX[nIdx]);
                }
            }
        }
        
        /* Start the iteration */
        while(nIterCtr < nMaxIter &&  nDiff > nTol)
        {
            for(nIdx = 0; nIdx < nSize; nIdx++)
            {
                double nSumRow;
                int    nCol;
                nSumRow = pInputB[nIdx];
                for(nCol = 0; nCol < nSize; nCol++)
                {
                    if(nCol != nIdx)
                    {
                        double  nEffectiveP;
                        /* Use the new points its has already been computed. */
                        nEffectiveP = nCol < nIdx ?  pOuputXNew[nCol] : pOuputX[nCol];
                        nSumRow -= (MATRIXE(pMatrix,nIdx,nCol,nSize) * nEffectiveP);
                    }
                }
                /* Compute the new value */
                pOuputXNew[nIdx] = nSumRow/MATRIXE(pMatrix,nIdx,nIdx,nSize); 
            }

            nDiff = 0;
            /* Calculate the new iteration difference 
               and assign the new values */
            for(nIdx = 0; nIdx < nSize; nIdx++)
            {
                /* compute the difference */
                nDiff += fabs(pOuputXNew[nIdx] - pOuputX[nIdx]);
                pOuputX[nIdx] = pOuputXNew[nIdx];
                /* Display iteration values */
                if(nDispIter)
                {
                    if(nIdx)
                        printf(" %2.7lf ",pOuputX[nIdx]);
                    else
                    {
                        printf("\n (%02d) ",nIterCtr);
                        printf(" %2.7lf ",pOuputX[nIdx]);
                    }
                }
            }
            nIterCtr++;
        }

        if(nDiff < nTol)
            *pnActualIter = nIterCtr;
        else
            nRet = -3;
    }

   /* Free the allocation */
    if(pOuputXNew)     free(pOuputXNew);
    return nRet;
}

