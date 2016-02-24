
#include "UpperTriangle.h"


/*--------------------------------------------------------------------------------*
* Function name       : upperTriangleAndBackSub
* Description         : Solves the upper trianglarization followed by back substitution
*                       
* Parameter(s)        : 
*	 *pAugMatrix	    [in]  The ugmented matrix [n x (n + 1)]
*                             Location of A(r,c) is at pAugMatrix[r-1][c-1].
*                       
*	 nSize		        [in]  The size of the matrix.
*                       
*	 *pOutputVector		[out] The ouput vactor.
*                             The first element is starts a pOutputVector[0].												
*                       
* Return              :     
*    int                 0 of successful.
*                        -1 - Unsucessful. Memory allocation failed.
*                        -2 - Unsucessful. Matrix maybe singular.
*                 
* Author              : Prime
*                 
* Revision(s)         :         
* 0.0.0 	Prime	2/24/2004	Initial release.
*--------------------------------------------------------------------------------*/
int __cdecl  
upperTriangleAndBackSub(double  *pAugMatrix,int nSize,double *pOutputVector)
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
		memset(pOutputVector,0,sizeof(pOutputVector[0]) * nSize);

		/* Start the upper triangularization */
		for(nPvtRowIdx = 0; nPvtRowIdx < (nSize - 1); nPvtRowIdx++)
		{
			
			int nRowIndex;
			int nPvtColIdx;

			nPvtColIdx = nPvtRowIdx;


			/* Search for the largest pivot element to reduce error */
			for(nRowIndex = nPvtRowIdx + 1; nRowIndex < nSize; nRowIndex++)
			{
				if(fabs(MATRIXE(pAugMatrix,pRow[nRowIndex],nPvtColIdx,nSize + 1)) > 
					fabs(MATRIXE(pAugMatrix,pRow[nPvtRowIdx],nPvtColIdx,nSize + 1)))
				{
					/* Since there is a larger value then swap the row */
					/* Note: this is only an indirect swapping, only the indices
					         are being swapped */
					int nTemp;

					nTemp = pRow[nRowIndex];
					pRow[nRowIndex]  = pRow[nPvtRowIdx];
					pRow[nPvtRowIdx] = nTemp;

				}
			}

			
			
			/* Check if the pivot element is row */
			if(MATRIXE(pAugMatrix,pRow[nPvtRowIdx],nPvtColIdx,(nSize + 1)) == 0)
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
				double  nMul;
				int i;

				/* Compute the multiplier */
				nMul = MATRIXE(pAugMatrix,pRow[nRowIndex],nPvtColIdx,(nSize + 1)) /
					   MATRIXE(pAugMatrix,pRow[nPvtRowIdx],nPvtColIdx,(nSize + 1)); 


				/* Since this will surely be 0, Clear the row index */
				MATRIXE(pAugMatrix,pRow[nRowIndex],nPvtColIdx,(nSize + 1)) = 0;

				/* Adjust the remaining values of the row*/
				for(i = nPvtColIdx + 1;i < (nSize + 1); i++)
				{
					MATRIXE(pAugMatrix,pRow[nRowIndex],i,(nSize + 1)) -= 
						(MATRIXE(pAugMatrix,pRow[nPvtRowIdx],i,(nSize + 1)) * nMul);
				}
			}
		}
	}

	if(nRet == 0)
	{
		/* Check if the AugMatrix[n,n] is 0 */
		if(MATRIXE(pAugMatrix,pRow[nSize - 1],(nSize - 1),(nSize + 1))  == 0)
		{
			/* Failed, Matrix is singular */ 
			nRet = -2;
		}
	}


	if(nRet == 0)
	{
		/* Back substitution */
		pOutputVector[nSize -1] = 
			MATRIXE(pAugMatrix,pRow[nSize - 1],(nSize),(nSize + 1)) /
			MATRIXE(pAugMatrix,pRow[nSize - 1],(nSize - 1),(nSize + 1));

		for(nPvtRowIdx = nSize - 2; nPvtRowIdx >= 0; nPvtRowIdx--)
		{
			double nSum = 0;
			int    i;

			for(i = nPvtRowIdx + 1; i < nSize; i++)
			{
				nSum += MATRIXE(pAugMatrix,pRow[nPvtRowIdx],i,(nSize + 1)) * pOutputVector[i];
			}

			pOutputVector[nPvtRowIdx] = (MATRIXE(pAugMatrix,pRow[nPvtRowIdx],nSize,(nSize + 1)) - nSum) / 
				MATRIXE(pAugMatrix,pRow[nPvtRowIdx],nPvtRowIdx,(nSize + 1)); 
		}
	}


	/* Deallocate the memory */
	if(pRow)
		free(pRow);
	

	return nRet;
}


