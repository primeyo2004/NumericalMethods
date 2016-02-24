#include "stdafx.h"
#include <math.h>
#include <conio.h>
#include "LgrngApx.h"
double   functionOfX(double fx);
int main(int argc, char* argv[])
{
	/* This will be the sample input and sample output */
	const double nInputXValues[]   = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2};
	/* Lets makes the degree variable which may  range from 1 - 12	*/
	double nXNodes[sizeof(nInputXValues)/sizeof(nInputXValues[0])];
	double nYNodes[sizeof(nInputXValues)/sizeof(nInputXValues[0])];
	int    nDegree;
	int    i,k;
	int    nSampleCount = sizeof(nInputXValues)/sizeof(nInputXValues[0]);
	printf("\n *** Lagrange Approximation program *** \n");
	printf("\n\n f(x) = sin(x) \n");
	/*  This is the input stage */
	do{
		printf("\n Enter the polynomial degree [1 - %d]: ",nSampleCount-1);
		scanf("%d",&nDegree); fflush(stdin);
	}while(nDegree <= 0 || nDegree > (nSampleCount-1));

	printf("\n");
	for(i = 0; i <= nDegree; i++)
	{
		int j;
		int distinct = 1;
		do{
		printf(" Enter a distinct known point X%d (must be within [%2.2lf,%2.2lf]): "
			   ,i,nInputXValues[0],nInputXValues[nSampleCount - 1]);
		scanf("%lf",&nXNodes[i]);
		/* Check if distinct */
		for(j = 0; j < i; j++)
		{
			if(nXNodes[i] == nXNodes[j])
			{
				distinct = 0;
				break;
			}
		}
		fflush(stdin);

		}while(nXNodes[i] < nInputXValues[0] 
			|| nXNodes[i] > nInputXValues[nSampleCount - 1] || distinct == 0);
		/* Compute the y value using f(x) */
		nYNodes[i]	= functionOfX(nXNodes[i]);
	}
	
	/*  This is computation/output stage  */
	/* ------------------------------------------------ */
	printf("\n\n                   ***   Result  ***              \n\n");
	printf("\n---------------------------------------------------------\n");
	printf("\n   Xk       f(xk)      Pn(xk)    | f(xk) - Pn(xk) | ");
	for(k = 0; k < nSampleCount; k++)
	{
		double  Fx;
		double  Px;
		Fx = functionOfX(nInputXValues[k]);
		Px = lagrangeApprox(nDegree,nXNodes,nYNodes,nInputXValues[k]);
		printf("\n %2.6lf   %2.6lf  %2.6lf  %2.6lf",nInputXValues[k],Fx,Px,fabs(Fx-Px));
	}
	printf("\n---------------------------------------------------------\n");
	printf("\npress any key to continue..");
	/* remove all inputs from the buffer */ 
	while(kbhit());
	getch();
	return 0;
}
/* This will be the function of X which is currently equal to sin(x). */
double    
functionOfX(double x)
{	return sin(x); }


