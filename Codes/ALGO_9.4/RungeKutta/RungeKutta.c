#include  <memory.h>
#include  <stdio.h>
#include  <conio.h>
#include  "RungeKuttaFunc.h"
double  funcTY(double nT,double nY); /* The function y'   */

int main(int argc, char* argv[])
{
    int nStatus = 0;

    int  i;
    double*  pTPoints = NULL;
    double*  pYPoints = NULL;
    
    int      nInterval;
    double   nLowerLimit;
    double   nUpperLimit;
    double   nInitYValue;

    printf("\n ***  Runge-Kutta Method of Order 4 *** \n");
    printf("\n y'   =  (t - y)/2        \n\n");

    /*  This is the input stage */
    /* ------------------------------------------------ */
    printf(" Enter the lower limit: ");
    scanf("%lf",&nLowerLimit);   fflush(stdin);
    printf(" Enter the upper limit: ");
    scanf("%lf",&nUpperLimit);   fflush(stdin);

    /*  Ask for the interval*/
    do{
        printf(" Enter the interval M  [ > 0]: ");
        scanf("%d",&nInterval);    fflush(stdin);
    }while(nInterval <= 0);

    /*  Ask for the initial value y(0)*/
    printf(" Enter the initial value y(0): ");
    scanf("%lf",&nInitYValue);   fflush(stdin);
    pTPoints = (double*) malloc((nInterval + 1) * sizeof(pTPoints[0]));
    pYPoints = (double*) malloc((nInterval + 1) * sizeof(pYPoints[0]));
    if(!pTPoints || !pYPoints)    nStatus = -1;
    
    if(nStatus == 0)
    {
        computeRungeKutta(nLowerLimit,nUpperLimit,nInitYValue,nInterval,funcTY,pTPoints,pYPoints);
        printf("\n Result:");
        printf("\n -------------------------- ");
        printf("\n   t(k)     \t     y(k)     ");
        for(i = 0; i <= nInterval; i++ )
            printf("\n %2.8lf \t  %2.8lf",pTPoints[i],pYPoints[i]);

        printf("\n -------------------------- ");
    }
    /* Report any errors */
    switch(nStatus)
    {
    case -1:
        printf("\nMemory allocation error!!");
        break;
    default:
        break;
    }
    /* Free the allocation */
    if(pTPoints)    free(pTPoints);
    if(pYPoints)    free(pYPoints);
    printf("\nPress any key to continue....");
    getch();
    return 0;
}
/* Evaluates the function y'  */
double  funcTY(double nT,double nY)
{    return ((nT - nY) / 2); }

