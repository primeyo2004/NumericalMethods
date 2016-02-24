#include <stdio.h>
#include <conio.h>
#include "BisectionFunc.h"

double  fFunc(double x);

int main(int argc, char* argv[])
{
    int nStatus = 0;
    double  nA;
    double  nB;
    double  nAccuracy;
    double  nRoot;
    
    printf("\n     *** Bisection Method *** ");
    printf("\n\n Using f(x) = x sin (x) - 1  ");

    /* Ask for input */
    printf("\n\n Enter the value for point A : ");
    scanf("%lf",&nA);  fflush(stdin);
    printf(" Enter the value for point B : ");
    scanf("%lf",&nB);   fflush(stdin);

    /* Compute the bisection method */
    nStatus = computeBisection(nA,nB,fFunc,1,&nRoot,&nAccuracy);

    if(nStatus == 0)
    {
        printf("\n The computed root is : %2.8lf",nRoot);
        printf("\n The accuracy is  +-  : %2.8lf",nAccuracy);
        printf("\n The function value at root is : %2.8lf",fFunc(nRoot));
    }
    else
    {
        printf("\n Error: f(A) and f(B) have same sign: [%2.8lf,%2.8lf]",fFunc(nA),fFunc(nB));
    }

    printf("\n\nPress any key to continue....");

    getch();
    return 0;
}

/* The f(x) function */
double  fFunc(double x)
{   return ((x  * sin(x)) - 1); }



