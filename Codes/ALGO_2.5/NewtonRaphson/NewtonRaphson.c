#include <stdio.h>
#include <conio.h>
#include "NewtonRaphsonFunc.h"

double  fFunc(double x);   /* The function of x */
double  fFunc1(double x);  /* The first derivative of a function */

int main(int argc, char* argv[])
{
    int nStatus = 0;
    double  nPn;
    double  nRoot;
    double  nDp;
    int     nMaxIter = 0;
    int     nIterCnt = 0;

	/* Input */
    printf("\n     *** Newton-Raphson Method *** ");
    printf("\n\n Using f(x)  = x^3 - 3x + 2  ");
    printf("\n\n       f'(x) = 2*x^2 - 3 ");
    printf("\n\n Enter the initial value P0 : ");
    scanf("%lf",&nPn);   fflush(stdin);

    printf(" Enter the maximum number of iteration : ");
    scanf("%d",&nMaxIter);     fflush(stdin);

	/* Compute the root */
    nStatus = computeNewtonRaphson(nPn,fFunc,fFunc1,nMaxIter,1,&nRoot,&nDp,&nIterCnt);

    switch(nStatus)
    {
    case 0:
        /* Sucess */    
        printf("\n The root was found with the desired tolerance.");
        printf("\n The computed root is           : %2.8lf",nRoot);
        printf("\n Consecutive iterates differ by : %2.8lf",nDp);
        printf("\n The function value at root is  : %2.8lf",fFunc(nRoot));
        printf("\n The number of iteration is     : %d",nIterCnt);
        break;
    case -1:
        printf("\n Failed: The maximum number of iteration was exceeded.");
        break;
    case -2:
        printf("\n Failed: Divide by zero error.");
        break;

    }

    printf("\n\nPress any key to continue....");

    getch();
    return 0;
}


/* The f(x) function */
double  fFunc(double x)
{
    return (pow(x,3) - 3*x + 2);
}

/* The first derivative of a function */
double  fFunc1(double x)
{
    return (3*pow(x,2) - 3);
}


