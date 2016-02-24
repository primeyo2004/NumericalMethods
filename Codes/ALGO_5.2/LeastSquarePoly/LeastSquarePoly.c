#include <stdio.h>
#include <conio.h>
#include "LSPolyFunc.h"

int main(int argc, char* argv[])
{
    int     nStatus = 0;
    int     nNumPoints,nPolyDegree;
    double  *pnXPoints = NULL, *pnYPoints = NULL, *pnCoefOutput = NULL;

    printf("\n  ***  Least-Squares Polynomial *** \n");
    /*  This is the input stage */
    printf("\n Enter the number of data points : ");
    scanf("%d",&nNumPoints);   fflush(stdin);
    printf("\n Enter the polymonial degree     :");
    scanf("%d",&nPolyDegree);  fflush(stdin);
    /* Allocate memory */
    pnXPoints          = (double*) malloc(nNumPoints * sizeof(pnXPoints[0]));
    pnYPoints          = (double*) malloc(nNumPoints * sizeof(pnYPoints[0]));
    pnCoefOutput       = (double*) malloc((nPolyDegree + 1) * sizeof(pnCoefOutput[0]));
    
    if(!pnXPoints || !pnYPoints || !pnCoefOutput)   nStatus = -1;
    if(nStatus == 0)
    {
        int i;
        /* Ask for the points */
        for(i = 0; i < nNumPoints; i++)
        {
            printf(" Enter the value for (X%d): ",i);
            scanf("%lf",&pnXPoints[i]); fflush(stdin);
            printf(" Enter the value for (Y%d): ",i);
            scanf("%lf",&pnYPoints[i]); fflush(stdin);
        }
    }

    /*  This is the computation stage */
    if(nStatus == 0)
    {
        nStatus = computeLSPoly(pnXPoints,pnYPoints,nNumPoints,nPolyDegree,pnCoefOutput);
        if(nStatus)  nStatus -= 2;
    }
    /*  Display */
    if(nStatus == 0)
    {
        int i,j,nPrint = 0;
        printf("\n The least-squares polynomial: \n P%d = ",nPolyDegree);
        for(j = 0; j <=  nPolyDegree; j++)
        {
            if(pnCoefOutput[j])
            {
                printf(" %c %2.8lf (x^%d)",(nPrint ? '+':' '),pnCoefOutput[j],nPolyDegree - j);
                nPrint++;
            }
        }
        printf("\n\n  ---------------------------- ");
        printf("\n\n N    \t     Xk     \t     Yk    \t     f(Xk) \n");
        for(i = 0; i < nNumPoints; i++)
        {
            double dblFx = 0;
            for(j = 0; j <=  nPolyDegree; j++)
                dblFx += (pnCoefOutput[j] * pow(pnXPoints[i],(double)nPolyDegree - j));
            printf("\n %d  \t %2.8lf \t %2.8lf \t %2.8lf",i,pnXPoints[i],pnYPoints[i],dblFx);
        }
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

    /* Free the Y Points */
    if(pnXPoints)  free(pnXPoints);
    if(pnYPoints)  free(pnYPoints);
    if(pnCoefOutput)  free(pnCoefOutput);
    getch();
    return nStatus;
}

