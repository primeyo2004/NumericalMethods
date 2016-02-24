#include <stdio.h>
#include <conio.h>
#include "CompSimpFunc.h"

double  functionOfX(double nX);

int main(int argc, char* argv[])
{

    int     i;
    double  nLowerLimit;
    double  nUpperLimit;
    int     nStartingInterval;
    int     nNumberOfSamples;

    printf("\n ***  Composite Simpson's Rule *** \n");
    printf("\n f(x) =  2x cos (x) dx \n\n");

    /*  This is the input stage */
    printf(" Enter the lower limit: ");
    scanf("%lf",&nLowerLimit);   fflush(stdin);
    printf(" Enter the upper limit: ");
    scanf("%lf",&nUpperLimit);   fflush(stdin);
    
    do{
        printf(" Enter the interval M      [ >= 10]: ");
        scanf("%d",&nStartingInterval);  fflush(stdin);
    }while(nStartingInterval < 10);

    do{
        printf(" Enter the number of samples [ > 0]: ");
        scanf("%d",&nNumberOfSamples); fflush(stdin);
    }while(nNumberOfSamples <= 0);


    /* Compute and display the output */
    printf("\n Result : \n");
    printf("\n ---------------------------- ");
    printf("\n   M      \t      h      \t      T(f,h)   ");
    for(i = 0; i < nNumberOfSamples; i++)
    {
        double nResult;
        computeCompSimpson(nLowerLimit,nUpperLimit,nStartingInterval,functionOfX,&nResult);
        printf("\n %8d   \t  %2.8lf  \t   %2.8lf",nStartingInterval,(nUpperLimit - nLowerLimit) / (double) (nStartingInterval * 2),nResult);
        nStartingInterval *= 2;
    }

    printf("\n ---------------------------- \n");
    printf("\n Press any key to continue....");
    getch();

    return 0;
}


double  functionOfX(double nX)
{
    return 2 * nX  * cos(nX);
    /*return (2 + sin(2 * sqrt(nX)));*/
}

