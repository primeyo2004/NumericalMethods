#include  <conio.h>
#include  <math.h>
#include  <conio.h>
#include  <memory.h>
#include  <malloc.h>
#include "LSLineFunc.h"
#include "NonLinearFunc.h"

int main(int argc, char* argv[])
{
    int     nStatus = 0;
    int     nNumPoints;
    double  *pnXPoints = NULL;
    double  *pnYPoints = NULL;
    double  *pnXOrigPoints = NULL;
    double  *pnYOrigPoints = NULL;
    double  nA,nB,nC,nD;

    int nForm;
    char    cChoice;

    printf("\n  ***  Non-Linear Curve Fitting *** \n");
    /*  This is the input stage */
    do{
        nForm = -1;

        printf("\n Select the nonlinear form you wish to fit:\n");
        printf("\n ----------------------------------------------------");
        printf("\n\n 1 ) y = A/ x + B          2) y = D / [x + C]     ");
        printf("\n\n 3 ) y = 1/ [Ax + B]       4) y = x / [A + Bx]    ");
        printf("\n\n 5 ) y = A * ln (x) + B    6) y = C * exp(Ax)     ");
        printf("\n\n 7 ) y = C * x^(A)         8) y = [Ax + B] ^ (-2) ");
        printf("\n\n ----------------------------------------------------\n");

        cChoice = getch();

        switch(cChoice)
        {
        case '1':   case '2':   case '3': case '4':    
        case '5':   case '6':   case '7': case '8':
            nForm = (cChoice & 0x0f)-1;
            break;
        default:
            break;
        }

    }while(nForm < 0 || nForm > 7);
    
    printf("\n Enter the number of data points : ");
    scanf("%d",&nNumPoints);  fflush(stdin);

    /* Allocate memory */
    pnXPoints          = (double*) malloc(nNumPoints * sizeof(pnXPoints[0]));
    pnYPoints          = (double*) malloc(nNumPoints * sizeof(pnYPoints[0]));
    pnXOrigPoints      = (double*) malloc(nNumPoints * sizeof(pnXOrigPoints[0]));
    pnYOrigPoints      = (double*) malloc(nNumPoints * sizeof(pnYOrigPoints[0]));

    if(!pnXPoints || !pnYPoints || !pnXOrigPoints || !pnYOrigPoints)
        nStatus = -1;

    if(nStatus == 0)
    {
        int i;
        /* Ask for the points */
        for(i = 0; i < nNumPoints; i++)
        {
            printf(" Enter the value for (X%d): ",i);
            scanf("%lf",&pnXPoints[i]); fflush(stdin);
			pnXOrigPoints[i] = pnXPoints[i];
            printf(" Enter the value for (Y%d): ",i);
            scanf("%lf",&pnYPoints[i]); fflush(stdin);
            pnYOrigPoints[i] = pnYPoints[i];
            
        }
    }
    /*  This is the computation stage */
    if(nStatus == 0)
    {
        nStatus = computeNonlinearCurve(nForm,pnXPoints,pnYPoints,nNumPoints,&nA,&nB,&nC,&nD);
        if(nStatus)   nStatus -= 2;
    }

    /*  Display */
    if(nStatus == 0)
    {
        int i;

        printf("\n The least-squares curve is: ");

        switch(nForm)
        {
        case 0:
            printf(" y = %2.8lf / x + %2.8lf",nA,nB);
            break;
        case 1:
            printf(" y = %2.8lf / [x + %2.8lf] ",nD,nC);
            break;
        case 2:
            printf(" y = 1 / [%2.8lfx + %2.8lf] ",nA,nB);
            break;
        case 3:
            printf(" y = x / [%2.8lf + %2.8lfx] ",nA,nB);
            break;
        case 4:
            printf(" y = %2.8lf * ln(x) + %2.8lf",nA,nB);
            break;
        case 5:
            printf(" y = %2.8lf * exp(%2.8lfx)",nC,nA);
            break;
        case 6:
            printf(" y = %2.8lf * x^(%2.8lf)",nC,nA);
            break;
        case 7:
            printf(" y = [%2.8lfx + %2.8lf] ^ (-2)",nA,nB);
            break;
        default:
            break;
        }

        printf("\n\n  ---------------------------- ");
        printf("\n\n N    \t     Xk     \t     Yk    \t     f(Xk) \n");
        for(i = 0; i < nNumPoints; i++)
        {
            double yVal = 0;
        
            switch(nForm)
            {
            case 0:
                yVal = nA / pnXOrigPoints[i] + nB;
                break;
            case 1:
                yVal =  nD / (pnXOrigPoints[i] + nC);
                break;
            case 2:
                yVal =  1 / (nA * pnXOrigPoints[i] + nB);
                break;
            case 3:
                yVal =  pnXOrigPoints[i] / (nA + nB * pnXOrigPoints[i]);
                break;
            case 4:
                yVal =  nA * log(pnXOrigPoints[i]) + nB;
                break;
            case 5:
                yVal =  nC * exp(nA * pnXOrigPoints[i]);
                break;
            case 6:
                yVal =  nC * pow(pnXOrigPoints[i],nA);
                break;
            case 7:
                yVal =  pow((nA * pnXOrigPoints[i]) + nB,-2);
                break;
            default:
                break;
            }

            printf("\n %d  \t %2.8lf \t %2.8lf \t %2.8lf",i,pnXOrigPoints[i],pnYOrigPoints[i], yVal);
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
        printf("\nFailed: Invalid nonlinear form!!");
        break;
    default:
        break;
    }

    printf("\n\nPress any key to continue...");

    /* Free the  Points */
    if(pnXPoints)   free(pnXPoints);
    
    if(pnYPoints)   free(pnYPoints);
    
    if(pnXOrigPoints) free(pnXOrigPoints);
    
    if(pnYOrigPoints)  free(pnYOrigPoints);

    getch();
    return nStatus;
}


