#include <stdio.h>
#include <conio.h>
#include "LUFactoring.h"
void  printEquations(double* pMatrix,double* pInputB,int nNumUnknown);

int main(int argc, char* argv[])
{
    double *pMatrix = NULL;
    int    *pPvtRowVect = NULL;
    double *pInputB = NULL;
    double *pOutputX = NULL;
    double deteminant;  int    nNumUnknown;    int    i,j;
    int    nStatus = 0;  /* -1 - Mem error,  -2 - Singular matrix */
    printf("\n  ***  PA = LU Factorization with Pivoting *** \n");
    /*  input stage */
    printf("\n Enter the number of unknowns : ");
    scanf("%d",&nNumUnknown);    fflush(stdin);
    /* Allocate memory */
    pMatrix = (double*) malloc(nNumUnknown * nNumUnknown * sizeof(pMatrix[0]));
    pPvtRowVect     = (int*) malloc(nNumUnknown * sizeof(pPvtRowVect[0]));
    pInputB         = (double*) malloc(nNumUnknown * sizeof(pInputB[0]));
    pOutputX        = (double*) malloc(nNumUnknown * sizeof(pOutputX[0]));
    if(!pMatrix || !pOutputX || !pPvtRowVect || !pInputB)      nStatus = -1;
    if(nStatus == 0)
    {   /* Ask for the coefficients & constant*/
        for(i = 0; i < nNumUnknown; i++)
        {   /* Ask for the coefficients */
            for(j = 0; j < nNumUnknown; j++)
            {
                printf(" Eq. (%d): Enter the coefficient for variable %c: ",i+1,j + 'A');
                scanf("%lf",&MATRIXE(pMatrix,i,j,nNumUnknown));  fflush(stdin);
            }
            /* Ask for the constant */
            printf(" Eq. (%d): Enter the equation constant: ",i+1);
            scanf("%lf",&pInputB[i]);  fflush(stdin);
        }
        /* print the equations */
        printEquations(pMatrix,pInputB,nNumUnknown);
    }

    /*  Computation */
    if(nStatus == 0) nStatus = constructLUP(pMatrix,nNumUnknown,pPvtRowVect,&deteminant);
    if(nStatus == 0) nStatus = computeXfromULP(pMatrix,nNumUnknown,pPvtRowVect,pInputB,pOutputX);
    /*  This is the display output stage */
    if(nStatus == 0)
    {
        printf("\nResult(s): ");
        for(i = 0; i < nNumUnknown; i++)
            printf("\n %c = %lf ",i + 'A',pOutputX[i]);
    }

    /* Free dynamic allocations */
    if(pMatrix)     free(pMatrix);
    if(pPvtRowVect) free(pPvtRowVect);
    if(pInputB)     free(pInputB);
    if(pOutputX)    free(pOutputX);

    switch(nStatus)
    {
    case -1:
        printf("\nMemory allocation error!!");
        break;
    case -2:
        printf("\nFailed: Matrix is singular!!");
        break;
    default:
        break;
    }
    printf("\n\nPress any key to continue...");
    getch();
    return nStatus;
}

void  
printEquations(double* pMatrix,double* pInputB,int nNumUnknown)
{
    int i,j;

    printf("\n Equations: ");
    printf("\n ------------------------------------------------ \n");

    /* Print the equations */
    for(i = 0; i < nNumUnknown; i++)
    {
        int nTermCount = 0;

        printf("Eq. (%d): ",i+1);


        /* Print the coefficients */
        for(j = 0; j < nNumUnknown; j++)
        {
            double coef;
            coef = MATRIXE(pMatrix,i,j,nNumUnknown);

            
            if(coef)
            {
                if(nTermCount)
                {
                    printf(" %c ",(coef >= 0) ? '+':'-');

                    coef = fabs(coef);
                }

                nTermCount++;
                printf("%2.6lf %c",coef,j + 'A');
            }
    

        }

        /* Ask for the constant */
        printf(" = %2.6lf\n",pInputB[i]);
    }

    printf("\n ------------------------------------------------ \n");

}


