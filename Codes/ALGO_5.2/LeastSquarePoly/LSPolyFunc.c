#include "LSPolyFunc.h"
#include "UpperTriangle.h"
/* Function name       : computeLSPoly
* Description         : Computes the coefficients A and B for a Least-Squares Polynomial.
* Parameter(s)        : 
*     *pXPoints         [in]  The X coordinate vector.
*     *pYPoints         [in]  The Y coordinate vector corresponding to each point in X.
*     nNumPoints        [in]  The number of elements or data points.
*     nNumPoints        [in]  The degree of the polynomial to be obtain.
*     pCoefficients     [out] The coefficient vector output.
* Return              :     
*    int _cdecl       0  - Success, -1  - Insufficient memory.
*                    -2  - Insufficient data points, -3  - Singular matrix.
*/
int _cdecl 
computeLSPoly(double *pXPoints,double *pYPoints,int nNumPoints,int nDegree,double* pCoefficients)
{
    int nRet = 0;
    int       nMatrixSize;
    double    *pAugmentedMatrix = NULL; /* The augmented matrix for the X^n and the constants */
    double    *pSumXPwrN        = NULL; /* The vetor of the summation of X^n */
    /* Must require atleast two points */
    if(nNumPoints <= 1)    nRet = -2;
    /* Allocate memory for the Augmented matrix and Summation of X of power N*/
    if(nRet == 0)
    {
		nMatrixSize = nDegree + 1;
        pAugmentedMatrix = (double*) malloc(nMatrixSize * (nMatrixSize + 1) * sizeof(pAugmentedMatrix[0]));
        pSumXPwrN        = (double*) malloc(((nDegree * 2) + 1) * sizeof(pSumXPwrN[0]));
		if(!pAugmentedMatrix || !pSumXPwrN)     nRet = -1;
    }
    /* Compute the summation of powers */
    if(nRet == 0)
    {
        int i,j;
        pSumXPwrN[0] = nNumPoints;
        for(i = 1; i < ((nDegree * 2) + 1); i++)
        {
            pSumXPwrN[i] = 0;
            for(j = 0; j < nNumPoints; j++)
                pSumXPwrN[i] += pow(pXPoints[j],(double)i);
        }
    }
    /* Compute and assign the constant vectors */
    if(nRet == 0)
    {
        int i,j;
        /*  B[i] = Sum( Y * X^(Degree - i) ) */
        for(i = 0; i < nMatrixSize; i++)
        {
            MATRIXE(pAugmentedMatrix,i,nMatrixSize,(nMatrixSize + 1))    = 0;
            for(j = 0; j < nNumPoints; j++)
            {
                MATRIXE(pAugmentedMatrix,i,nMatrixSize,(nMatrixSize + 1))    += 
                    (pYPoints[j] * pow(pXPoints[j],(double)(nDegree - i)));
            }
        }
    }
    /* Assign the matrix  */
    if(nRet == 0)
    {
        int i,j;
        /*  A[i,j] = Sum(X^(Degree * 2) - i - j) ) */
        for(i = 0; i < nMatrixSize; i++)
        {
            for(j = 0; j < nMatrixSize; j++)
            {
                MATRIXE(pAugmentedMatrix,i,j,(nMatrixSize + 1)) 
                    = pSumXPwrN[(nDegree * 2) - i - j];
            }
        }
    }
    /*  Now compute the linear system  */
    if(nRet == 0)
    {
        nRet = upperTriangleAndBackSub(pAugmentedMatrix,nMatrixSize,pCoefficients);
        /* Adjust the error to our convention */
        if(nRet == -2)  nRet--;
    }

    /* Deallocate the memory */
    if(pAugmentedMatrix)  free(pAugmentedMatrix);
    if(pSumXPwrN)         free(pSumXPwrN);

    return nRet;
}

