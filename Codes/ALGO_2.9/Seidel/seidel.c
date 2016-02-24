#include <stdio.h>
#include <conio.h>
#include "SeidelFunc.h"

double  gFunc1(double x,double y);   /* The g1 of x,y*/
double  gFunc2(double x,double y);   /* The g2 of x,y*/

int main(int argc, char* argv[])
{
    int nStatus = 0;
    double  nPn;
    double  nQn;
    double  nX;
    double  nY;
    int     nMaxIter = 0;
    int     nIterCnt = 0;

	/* Input */
    printf("\n   *** Nonlinear Seidel Iteration *** ");
    printf("\n\n Using f1(x,y)  = y - x^2 + 3 ");
    printf("\n\n Using f2(x,y)  = 3 - xy ");
    
    printf("\n\n Enter the initial value P0 : ");
    scanf("%lf",&nPn);  fflush(stdin);

    printf(" Enter the initial value Q0 : ");
    scanf("%lf",&nQn);  fflush(stdin);

    printf(" Enter the maximum number of iteration : ");
    scanf("%d",&nMaxIter);  fflush(stdin);

	/* Compute the roots */
    nStatus = computeSeidel(nPn,nQn,gFunc1,gFunc2,nMaxIter,1,&nX,&nY,&nIterCnt);

    switch(nStatus)
    {
    case 0:
        /* Sucess */    
        printf("\n Solution was found after %d iterations. ",nIterCnt);
        printf("\n x  : %2.8lf",nX);
        printf("\n y  : %2.8lf",nY);
        break;
    case -1:
        printf("\n Failed: Seidel iteration did not converge.");
        break;
    default:
        break;
    }

    printf("\n\nPress any key to continue....");

    getch();
    return 0;
}



double  gFunc1(double x,double y)   /* The g1 of x,y */
{
    return ((4*x - pow(x,2) + y + 3)/4);
}

double  gFunc2(double x,double y)   /* The g2 of x,y */
{
    return ((3 - x*y + 2 * y)/2);
}

