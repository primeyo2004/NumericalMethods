#include <conio.h>
#include "UpperTriangle.h"

void  printEquations(double* pAugMtrx,int nNumUnknown);

int main(int argc, char* argv[])
{
    double *pAugMtrx = NULL;
    double *pOutput = NULL;
    int    nNumUnknown;
    int    i,j;
    int    nStatus = 0;  /* -1 - Mem error,  -2 - Singular matrix */
    printf("\n  ***  Upper Triangularization with Back Substitution *** \n");
    /*  This is the input stage */
    printf("\n Enter the number of unknowns  : ");
    scanf("%d",&nNumUnknown); fflush(stdin);
    /* Allocate memory */
    pAugMtrx = (double*) malloc(nNumUnknown * (nNumUnknown + 1) * sizeof(pAugMtrx[0]));
    pOutput          = (double*) malloc(nNumUnknown * sizeof(pOutput[0]));
    if(!pAugMtrx || !pOutput)        nStatus = -1;
    if(nStatus == 0)
    {
        /* Ask for the coefficients & constant*/
        for(i = 0; i < nNumUnknown; i++)
        {
            /* Ask for the coefficients */
            for(j = 0; j < nNumUnknown; j++)
            {
                printf(" Eq. (%d): Enter the coefficient for variable %c: ",i+1,j + 'A');
                scanf("%lf",&MATRIXE(pAugMtrx,i,j,(nNumUnknown + 1)));   fflush(stdin);
            }

            /* Ask for the constant */
            printf(" Eq. (%d): Enter the equation constant: ",i+1);
            scanf("%lf",&MATRIXE(pAugMtrx,i,nNumUnknown,(nNumUnknown + 1)));   fflush(stdin);
        }

        /* print the equations */
        printEquations(pAugMtrx,nNumUnknown);
    }
    /*  Solve the linear system */
    if(nStatus == 0)   nStatus = upperTriangleAndBackSub(pAugMtrx,nNumUnknown,pOutput);
    /*  This is the display output stage */
    if(nStatus == 0)
    {
        printf("\nResult(s): ");
        for(i = 0; i < nNumUnknown; i++)
            printf("\n %c = %lf ",i + 'A',pOutput[i]);
    }
    /* Free dynamic allocations */
    if(pAugMtrx)
        free(pAugMtrx);
    if(pOutput)
        free(pOutput);

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
printEquations(double* pAugMtrx,int nNumUnknown)
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
            coef = MATRIXE(pAugMtrx,i,j,(nNumUnknown + 1));

            
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
        printf(" = %2.6lf\n",MATRIXE(pAugMtrx,i,nNumUnknown,(nNumUnknown + 1)));
    }

    printf("\n ------------------------------------------------ \n");

}

