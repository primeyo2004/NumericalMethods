#include <stdio.h>
#include <conio.h>
#include "FixedPointFunc.h"

double  gFunc(double x);

int main(int argc, char* argv[])
{
    int nStatus = 0;
    double  nP0;
    double  nRelativeError;
    double  nP;
    int     nMaxIter;

    printf("\n     *** Fixed-Point Iteration *** ");
    printf("\n\n Using g(x) = -4 + 4x - x^2/2  ");

    /* Ask for input */
    printf("\n\n Enter the initial value P0 : ");
    scanf("%lf",&nP0);    fflush(stdin);
    printf(" Enter the maximum number of iterations: ");
    scanf("%d",&nMaxIter);
    fflush(stdin);

    /* Copmpute the the fixed-point iteration */
    nStatus = computeFixedPoint(nP0,gFunc,nMaxIter,200,1,&nP,&nRelativeError);

    /* Display output */
    if(nStatus == 0)
    {
        printf("\n The computed fixed point is : %2.8lf",nP);
        printf("\n The the relative error is   : %2.8lf",nRelativeError);
    }
    else
    {
        printf("\n The sequence appears tobe diverging.");
    }

    printf("\n\nPress any key to continue....");

    getch();
    return 0;
}


/* The g(x) function */
double  gFunc(double x)
{
    return -4 + 4 * x  - pow(x,2)/2;
}



