#include "LUFactoring.h"
/* Function name      : constructLUP
* Description         : Constructs the L and U  of a matrix and the vector
*                       containing the row indices as a result of row interchange.  
* Parameter(s)        : 
*     *pMatrix            [in]   The coefficient matrix [n x n]
*                                Location of A(r,c) is at pMatrix[r-1][c-1].
*     nSize                [in]  The size of the matrix.
*     *pPvtRowVect         [out] The row indices due to permutation/ row interchange.
*     pDeterminant         [out] The determinant of the matrix.
* Return              :     
*    int                 0 of successful, -1 - Memory allocation failed,
*                        -2 - Matrix maybe non-singular.
*/
int __cdecl 
constructLUP(double  *pMatrix,int nSize,int *pPvtRowVect,double* pDeterminant)
{
    int nRet = 0;
    int nPvtRowIdx;
    int *pRow = pPvtRowVect;
    *pDeterminant = 1;
    /* Initialize the row index */
    for(nPvtRowIdx = 0; nPvtRowIdx < nSize; nPvtRowIdx++) pRow[nPvtRowIdx] = nPvtRowIdx;
    /* Start the upper triangularization */
    for(nPvtRowIdx = 0; nPvtRowIdx < (nSize - 1); nPvtRowIdx++)
    {
        int nRowIndex;
        int nPvtColIdx;   nPvtColIdx = nPvtRowIdx;
        /* Search for the largest pivot element to reduce error */
        for(nRowIndex = nPvtRowIdx + 1; nRowIndex < nSize; nRowIndex++)
        {
            if(fabs(MATRIXE(pMatrix,pRow[nRowIndex],nPvtColIdx,nSize)) > 
                fabs(MATRIXE(pMatrix,pRow[nPvtRowIdx],nPvtColIdx,nSize)))
            {
                /* Since there is a larger value then swap the row */
                int nTemp;
                nTemp = pRow[nRowIndex];
                pRow[nRowIndex]  = pRow[nPvtRowIdx];
                pRow[nPvtRowIdx] = nTemp;
                /* Change the sign of the determinant */
                (*pDeterminant) *= -1;
            }
        }
        (*pDeterminant) *= MATRIXE(pMatrix,pRow[nPvtRowIdx],nPvtColIdx,nSize);
        /* Check if the pivot element is row */
        if(MATRIXE(pMatrix,pRow[nPvtRowIdx],nPvtColIdx,nSize) == 0)
        {
            nRet = -2;
            break;
        }
        /* Now eliminate the elements that is located below the
           pivot element.    
        */
        for(nRowIndex = nPvtRowIdx + 1; nRowIndex < nSize; nRowIndex++)
        {
            double  nMul;
            int i;
            /* Compute the multiplier */
            nMul = MATRIXE(pMatrix,pRow[nRowIndex],nPvtColIdx,(nSize)) /
                   MATRIXE(pMatrix,pRow[nPvtRowIdx],nPvtColIdx,(nSize)); 
            /* Assing the multiplier*/
            MATRIXE(pMatrix,pRow[nRowIndex],nPvtColIdx,(nSize)) = nMul;
            /* Adjust the remaining values of the row*/
            for(i = nPvtColIdx + 1;i < nSize; i++)
            {
                MATRIXE(pMatrix,pRow[nRowIndex],i,(nSize)) -= 
                    (MATRIXE(pMatrix,pRow[nPvtRowIdx],i,(nSize)) * nMul);
            }
        }
    }
    if(nRet == 0)
    {
        (*pDeterminant) *= MATRIXE(pMatrix,pRow[nSize - 1],(nSize - 1),nSize);
        /* Check if the Matrix[n,n] is 0 */
        if(MATRIXE(pMatrix,pRow[nSize - 1],(nSize - 1),nSize)  == 0) nRet = -2;
    }
    return nRet;
}
/* Function name      : computeXfromULP
* Description         : Computes the unknown vector from and LU and P.
* Parameter(s)        : 
*     *pMatrix            [in]  The ugmented matrix [n x n]
*                              Location of A(r,c) is at pMatrix[r-1][c-1].
*     nSize               [in]  The size of the matrix.
*     *pPvtRowVect        [in]  The row indices due to permutation/ row interchange.
*     pInputB             [in]  The constants.
*     pOuputX             [out] The unknown vector.
* Return              :     
*    int                 0 of successful, -1 - Memory allocation failed.
*                        -2 - Matrix maybe non-singular.
*/
int  __cdecl 
computeXfromULP(double  *pMatrix,int nSize,int *pPvtRowVect,double* pInputB,double* pOuputX)
{
    int nRet = 0;
    int      *pRow = pPvtRowVect;
    double   *pY   = NULL;
    int nIdx;

    /* Allocate the storage for the y */
    pY = (double*) malloc(nSize * sizeof(double));
    if(!pY)  nRet = -1;
    if(nRet == 0)
    {   /* Compute Y using the forward substitution */
        pY[0] = pInputB[pRow[0]];
        for(nIdx = 1; nIdx < nSize; nIdx++)
        {
            double  nSum = 0;
            int    i;
            for(i = 0; i < nIdx; i++)
                nSum += (MATRIXE(pMatrix,pRow[nIdx],i,nSize) * pY[i]);
            /* get the value of the current y */
            pY[nIdx] = pInputB[pRow[nIdx]] - nSum;
        }
        /* Check if the Matrix[n,n] is 0 */
        if(MATRIXE(pMatrix,pRow[nSize - 1],(nSize - 1),nSize)  == 0)
            nRet = -2;
    }
    if(nRet == 0)
    {   /* Start the back substitution */
        pOuputX[nSize -1] = pY[nSize -1] 
			              / MATRIXE(pMatrix,pRow[nSize - 1],(nSize - 1),nSize);
        for(nIdx = nSize - 2; nIdx >= 0; nIdx--)
        {
            double  nSum = 0;
            int    i;
            for(i = nIdx+1; i < nSize; i++)
            {
                nSum += MATRIXE(pMatrix,pRow[nIdx],i,nSize) * pOuputX[i];
            }
            if(MATRIXE(pMatrix,pRow[nIdx],nIdx,nSize) == 0)
            {   /* Failed, Matrix is singular */ 
                nRet = -2;
                break;
            }
            /* pMatrix[pRow[nIdx],nIdx] is assummed non-0 if constructLUP 
			   has been called using same parameters*/
            pOuputX[nIdx] = (pY[nIdx] - nSum) / MATRIXE(pMatrix,pRow[nIdx],nIdx,nSize) ;
        }
    }
    return nRet;
}


