#include <stdio.h>
#include <conio.h>
#include "FalsePositionFunc.h"

double  fFunc(double x);

int main(int argc, char* argv[])
{
    int nStatus = 0;
    double  nA;
    double  nB;
    double  nDx;
    double  nRoot;
    int     nMaxIter = 0;
    
	/* Ask for input */
    printf("\n     *** False Position or Regula Falsi Method *** ");
    printf("\n\n Using f(x) = x sin (x) - 1  ");
    printf("\n\n Enter the value for point A : ");
    scanf("%lf",&nA);  fflush(stdin);
    printf(" Enter the value for point B : ");
    scanf("%lf",&nB);  fflush(stdin);
    printf(" Enter the maximum number of iteration : ");
    scanf("%d",&nMaxIter);     fflush(stdin);

	/* Compute the the root */
    nStatus = computeFalsePosition(nA,nB,fFunc,nMaxIter,1,&nRoot,&nDx);

    if(nStatus == 0)
    {
        printf("\n The computed root is : %2.8lf",nRoot);
        printf("\n Consecutive iterates differ by : %2.8lf",nDx);
        printf("\n The function value at root is  : %2.8lf",fFunc(nRoot));
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
{
    return ((x  * sin(x)) - 1);
}



