#include <stdio.h>
#include <conio.h>
#include "Newton4dFunc.h"

/* The fn(x0,x1,x2,x3) */
double  fFunc0(double x0,double x1,double x2,double x3);
double  fFunc1(double x0,double x1,double x2,double x3);
double  fFunc2(double x0,double x1,double x2,double x3);
double  fFunc3(double x0,double x1,double x2,double x3);
/* The fn/dxn(x0,x1,x2,x3)*/
double  f0FuncDx0(double x0,double x1,double x2,double x3);   
double  f0FuncDx1(double x0,double x1,double x2,double x3);
double  f0FuncDx2(double x0,double x1,double x2,double x3);
double  f0FuncDx3(double x0,double x1,double x2,double x3);
double  f1FuncDx0(double x0,double x1,double x2,double x3);
double  f1FuncDx1(double x0,double x1,double x2,double x3);
double  f1FuncDx2(double x0,double x1,double x2,double x3);
double  f1FuncDx3(double x0,double x1,double x2,double x3);
double  f2FuncDx0(double x0,double x1,double x2,double x3);
double  f2FuncDx1(double x0,double x1,double x2,double x3);
double  f2FuncDx2(double x0,double x1,double x2,double x3);
double  f2FuncDx3(double x0,double x1,double x2,double x3);
double  f3FuncDx0(double x0,double x1,double x2,double x3);
double  f3FuncDx1(double x0,double x1,double x2,double x3);
double  f3FuncDx2(double x0,double x1,double x2,double x3);
double  f3FuncDx3(double x0,double x1,double x2,double x3);


int main(int argc, char* argv[])
{
    int nStatus = 0;
    double  nPn[4];
    double  nPnOut[4];
    int     i;
    int     nMaxIter = 0;
    int     nIterCnt = 0;
    Func4   augFuncMtrx[4][5];

    /* Assign the function  matrix  of derivatives*/
    augFuncMtrx[0][0] = f0FuncDx0;  augFuncMtrx[0][1] = f0FuncDx1;  
	augFuncMtrx[0][2] = f0FuncDx2;  augFuncMtrx[0][3] = f0FuncDx3;
    augFuncMtrx[1][0] = f1FuncDx0;  augFuncMtrx[1][1] = f1FuncDx1;
    augFuncMtrx[1][2] = f1FuncDx2;  augFuncMtrx[1][3] = f1FuncDx3;
    augFuncMtrx[2][0] = f2FuncDx0;  augFuncMtrx[2][1] = f2FuncDx1;
    augFuncMtrx[2][2] = f2FuncDx2;  augFuncMtrx[2][3] = f2FuncDx3;
    augFuncMtrx[3][0] = f3FuncDx0;  augFuncMtrx[3][1] = f3FuncDx1;
    augFuncMtrx[3][2] = f3FuncDx2; augFuncMtrx[3][3] = f3FuncDx3;

    /* Augment the function  */
    augFuncMtrx[0][4] = fFunc0;  augFuncMtrx[1][4] = fFunc1;
    augFuncMtrx[2][4] = fFunc2;  augFuncMtrx[3][4] = fFunc3;
    
    printf("\n   *** Newton-Raphson for 4D *** ");
    printf("\n\n---------------------------------------------");
    printf("\n\n Using: f0(x0,x1,x2,x3)  = x0 - 7.2 * x3^2 - 392.28 ");
    printf("\n\n        f1(x0,x1,x2,x3)  = x0 - 810 + 25 * x1 + 3.75 * x1^2 ");
    printf("\n\n        f2(x0,x1,x2,x3)  = x0 - 900 + 65 * x2 + 30 * x2^2 ");
    printf("\n\n        f3(x0,x1,x2,x3)  = x3 - x1 - x2 ");
    printf("\n\n---------------------------------------------");
    printf("\n\n");

	/* Input stage */
    for(i =0;i <4; i++)
    {
        printf(" Enter the initial value P%d : ",i);
        scanf("%lf",&nPn[i]);
        /* this will clean up the input buffer */
        fflush(stdin);
    }

    printf(" Enter the maximum number of iteration : ");
    scanf("%d",&nMaxIter);   fflush(stdin);

	/* Compute NR4D */
    nStatus = computeNewton4D(nPn,&augFuncMtrx[0][0],nMaxIter,1,nPnOut,&nIterCnt);

	/* Dispay output */
    switch(nStatus)
    {
    case 0:
        printf("\n Solution was found with the desired tolerance.\n");        
        printf("\n x0 = %2.8lf",nPnOut[0]);        
        printf("\n x1 = %2.8lf",nPnOut[1]);        
        printf("\n x2 = %2.8lf",nPnOut[2]);        
        printf("\n x3 = %2.8lf\n",nPnOut[3]);        
        printf("\n Number of iterations: %d",nIterCnt);        
        break;
    case -1:
        printf("\n Failed: Memory allocation in error.");        
        break;
    case -2:
        printf("\n Failed: Solution cannot be solve as "
			   " it yeild to a singular matrix.");        
        break;
    case -3:
        printf("\n Failed: Solution exceeded the maximum number of iterations.");        
        break;
    default:
        break;
    }

    printf("\n\nPress any key to continue....");

    getch();
    return 0;
}

double  fFunc0(double x0,double x1,double x2,double x3)
{    return (x0 - 7.2 * pow(x3,2) - 392.28); }

double  fFunc1(double x0,double x1,double x2,double x3)
{    return (x0 - 810 + 25 * x1 + 3.75 * pow(x1,2)); }

double  fFunc2(double x0,double x1,double x2,double x3)
{    return (x0 - 900 + 65 * x2 + 30 * pow(x2,2)); }

double  fFunc3(double x0,double x1,double x2,double x3)
{    return (x3 - x1 - x2); }

double  f0FuncDx0(double x0,double x1,double x2,double x3)
{    return 1; }

double  f0FuncDx1(double x0,double x1,double x2,double x3)
{    return 0; }
double  f0FuncDx2(double x0,double x1,double x2,double x3)
{    return 0; }
double  f0FuncDx3(double x0,double x1,double x2,double x3)
{    return (-1 * 14.4 * x3); }
double  f1FuncDx0(double x0,double x1,double x2,double x3)
{    return 1;}

double  f1FuncDx1(double x0,double x1,double x2,double x3)
{    return (25 + 7.5 * x1);}
double  f1FuncDx2(double x0,double x1,double x2,double x3)
{    return 0; }
double  f1FuncDx3(double x0,double x1,double x2,double x3)
{    return 0; }
double  f2FuncDx0(double x0,double x1,double x2,double x3)
{    return 1; }
double  f2FuncDx1(double x0,double x1,double x2,double x3)
{    return 0; }
double  f2FuncDx2(double x0,double x1,double x2,double x3)
{    return (65 + 60 * x2); }
double  f2FuncDx3(double x0,double x1,double x2,double x3)
{    return 0; }
double  f3FuncDx0(double x0,double x1,double x2,double x3)
{    return 0; }
double  f3FuncDx1(double x0,double x1,double x2,double x3)
{    return  -1; }
double  f3FuncDx2(double x0,double x1,double x2,double x3)
{    return -1;  }
double  f3FuncDx3(double x0,double x1,double x2,double x3)
{    return  1; }

