#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include "LSLineFunc.h"
int main(int argc, char* argv[])
{
    int     nStatus = 0;
    int     nNumPoints;
    double  *pnXPoints = NULL;
    double  *pnYPoints = NULL;
    double  nA;
    double  nB;
    printf("\n  ***  Least-Squares Line *** \n");
    /*  This is the input stage */
    printf("\n Enter the number of data points : ");
    scanf("%d",&nNumPoints);    fflush(stdin);
    /* Allocate memory */
    pnXPoints          = (double*) malloc(nNumPoints * sizeof(pnXPoints[0]));
    pnYPoints          = (double*) malloc(nNumPoints * sizeof(pnYPoints[0]));
    if(!pnXPoints || !pnYPoints)  nStatus = -1;
    if(nStatus == 0)
    {
        int i;
        /* Ask for the points */
        for(i = 0; i < nNumPoints; i++)
        {
            printf(" Enter the value for (X%d): ",i);
            scanf("%lf",&pnXPoints[i]);  fflush(stdin);
            printf(" Enter the value for (Y%d): ",i);
            scanf("%lf",&pnYPoints[i]);  fflush(stdin);
        }
    }
    /*  This is the computation stage */
    if(nStatus == 0)
    {
        nStatus = computeLSLine(pnXPoints,pnYPoints,nNumPoints,&nA,&nB);
        if(nStatus)  nStatus -= 2;
    }
    /*  Display */
    if(nStatus == 0)
    {
        int i;
        printf("\n The least-squares line: y = %2.8lf x + %2.8lf ",nA,nB);
        printf("\n\n  ---------------------------- ");
        printf("\n\n N    \t     Xk     \t     Yk    \t     f(Xk) \n");
        for(i = 0; i < nNumPoints; i++)
            printf("\n %d  \t %2.8lf \t %2.8lf \t %2.8lf"
			,i,pnXPoints[i],pnYPoints[i], (nA * pnXPoints[i] + nB));
        printf("\n\n  ---------------------------- ");
    }

    switch(nStatus)
    {
    case -1:
        printf("\nMemory allocation error!!");
        break;
    case -2:
        printf("\nFailed: Insuffient data points!!");
        break;
    case -3:
        printf("\nFailed: Determinant is 0!!");
        break;
    default:
        break;
    }
    printf("\n\nPress any key to continue...");
    /* Free the Points */
    if(pnXPoints)  free(pnXPoints);
    if(pnYPoints)  free(pnYPoints);
    getch();
    return nStatus;
}

