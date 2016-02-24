#include "UpperTriangle.h"
/* Function name      : upperTriangleAndBackSub
* Description         : Solves a linear system by upper triangularization followed by back substitution
* Parameter(s)        : 
*     *pAugMtrx        [in]  The ugmented matrix [n x (n + 1)]
*                            Location of A(r,c) is at pAugMtrx[r-1][c-1].
*     nSize            [in]  The size of the matrix.
*     *pOutVect        [out] The ouput vactor.
*                            The first element is starts a pOutVect[0].                                                
* Return              :     
*    int                 0 - successful, -1 Memory allocation failed, -2 Matrix maybe singular.
*/
int __cdecl  
upperTriangleAndBackSub(double  *pAugMtrx,int nSize,double *pOutVect)
{
    int nRet = 0;
    int nPvtRowIdx;
    int *pRow = NULL;
    pRow = (int *)malloc(nSize * sizeof(int));

    if(!pRow)
        nRet = -1;

    if(nRet == 0)
    {
        /* Initialize the row index */
        for(nPvtRowIdx = 0; nPvtRowIdx < nSize; nPvtRowIdx++)
            pRow[nPvtRowIdx] = nPvtRowIdx;

        /* Initialize the ouput vector */
        memset(pOutVect,0,sizeof(pOutVect[0]) * nSize);

        /* Start the upper triangularization */
        for(nPvtRowIdx = 0; nPvtRowIdx < (nSize - 1); nPvtRowIdx++)
        {
            int nRowIndex;
            int nPvtColIdx;
            nPvtColIdx = nPvtRowIdx;
            /* Search for the largest pivot element to reduce error */
            for(nRowIndex = nPvtRowIdx + 1; nRowIndex < nSize; nRowIndex++)
            {
                if(fabs(MATRIXE(pAugMtrx,pRow[nRowIndex],nPvtColIdx,nSize + 1)) > 
                    fabs(MATRIXE(pAugMtrx,pRow[nPvtRowIdx],nPvtColIdx,nSize + 1)))
                {
                    /* Since there is a larger value then swap the row */
                    int nTemp;
                    nTemp = pRow[nRowIndex];
                    pRow[nRowIndex]  = pRow[nPvtRowIdx];
                    pRow[nPvtRowIdx] = nTemp;
                }
            }
            
            if(MATRIXE(pAugMtrx,pRow[nPvtRowIdx],nPvtColIdx,(nSize + 1)) == 0)
            {
                /* Failed, Matrix is singular */ 
                nRet = -2;
                break;
            }
            
            /* Now eliminate the elements that is located below the
               pivot element.    
            */
            for(nRowIndex = nPvtRowIdx + 1; nRowIndex < nSize; nRowIndex++)
            {
                double  nMul; int i;
                /* Compute the multiplier */
                nMul = MATRIXE(pAugMtrx,pRow[nRowIndex],nPvtColIdx,(nSize + 1)) /
                       MATRIXE(pAugMtrx,pRow[nPvtRowIdx],nPvtColIdx,(nSize + 1)); 

                MATRIXE(pAugMtrx,pRow[nRowIndex],nPvtColIdx,(nSize + 1)) = 0;

                for(i = nPvtColIdx + 1;i < (nSize + 1); i++)
                {
                    MATRIXE(pAugMtrx,pRow[nRowIndex],i,(nSize + 1)) -= 
                        (MATRIXE(pAugMtrx,pRow[nPvtRowIdx],i,(nSize + 1)) * nMul);
                }
            }
        }
    }

    if(nRet == 0)
    {
        /* Check if the AugMatrix[n,n] is 0 */
        if(MATRIXE(pAugMtrx,pRow[nSize - 1],(nSize - 1),(nSize + 1))  == 0)
            nRet = -2;
    }

    if(nRet == 0)
    {
        /* Back substitution */
        pOutVect[nSize -1] = 
            MATRIXE(pAugMtrx,pRow[nSize - 1],(nSize),(nSize + 1)) /
            MATRIXE(pAugMtrx,pRow[nSize - 1],(nSize - 1),(nSize + 1));

        for(nPvtRowIdx = nSize - 2; nPvtRowIdx >= 0; nPvtRowIdx--)
        {
            double nSum = 0;
            int    i;

            for(i = nPvtRowIdx + 1; i < nSize; i++)
            {
                nSum += MATRIXE(pAugMtrx,pRow[nPvtRowIdx],i,(nSize + 1)) * pOutVect[i];
            }

            pOutVect[nPvtRowIdx] = (MATRIXE(pAugMtrx,pRow[nPvtRowIdx],nSize,(nSize + 1)) - nSum) / 
                MATRIXE(pAugMtrx,pRow[nPvtRowIdx],nPvtRowIdx,(nSize + 1)); 
        }
    }

    /* Deallocate the memory */
    if(pRow)
        free(pRow);
    
    return nRet;
}


