#include "GaussSeidelFunc.h"
#include <conio.h>
void  printEquations(double* pMatrix,double* pInputB,int nNumUnknown);

int main(int argc, char* argv[])
{
    int    nIterCnt;
    double *pMatrix = NULL;
    double *pInputB = NULL;
    double *pOutputX = NULL;
    int    nNumUnknown;     int    i,j;
    int    nStatus = 0;  /* -1 - Mem error,  -2 - Singular matrix */
    printf("\n  ***  Gauss-Seidel Iteration *** \n");
    /*  This is the input stage */
    printf("\n Enter the number of unknowns : ");
    scanf("%d",&nNumUnknown);   fflush(stdin);
    /* Allocate memory  */
    pMatrix  = (double*) malloc(nNumUnknown * nNumUnknown * sizeof(pMatrix[0]));
    pInputB  = (double*) malloc(nNumUnknown * sizeof(pInputB[0]));
    pOutputX = (double*) malloc(nNumUnknown * sizeof(pOutputX[0]));
    if(!pMatrix || !pOutputX || !pInputB)   nStatus = -1;
    if(nStatus == 0)
    {   /* Ask for the coefficients & constant*/
        for(i = 0; i < nNumUnknown; i++)
        {
            /* Ask for the coefficients */
            for(j = 0; j < nNumUnknown; j++)
            {
                printf(" Eq. (%d): Enter the coefficient for variable %c: ",i+1,j + 'A');
                scanf("%lf",&MATRIXE(pMatrix,i,j,nNumUnknown)); fflush(stdin);
            }
            /* Ask for the constant */
            printf(" Eq. (%d): Enter the equation constant: ",i+1);
            scanf("%lf",&pInputB[i]);   fflush(stdin);
        }
        /* print the equations */
        printEquations(pMatrix,pInputB,nNumUnknown);
    }
    if(nStatus == 0) /* Solve the system */
        nStatus = computeGaussSeidel(pMatrix,nNumUnknown,pInputB,pOutputX,100,&nIterCnt,1);

    /*  This is the display output stage */
    /* ------------------------------------------------ */
    if(nStatus == 0)
    {
        printf("\n\nResult(s): ");
        for(i = 0; i < nNumUnknown; i++)  printf("\n %c = %lf ",i + 'A',pOutputX[i]);
        printf("\n\nNumber of Iterations(s): %d",nIterCnt);
    }
    /* Free dynamic allocations */
    if(pMatrix)   free(pMatrix);
    if(pInputB)   free(pInputB);
    if(pOutputX)  free(pOutputX);
    switch(nStatus)
    {
    case -1:
        printf("\nMemory allocation error!!");
        break;
    case -2:
        printf("\nFailed: Not diagonally dominant!!");
        break;
    case -3:
        printf("\nFailed: Solution didn't converge!!");
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
