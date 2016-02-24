#include  <memory.h>
#include  <stdio.h>
#include  <conio.h>
#include  "TaylorO4Func.h"

double  funcTY1(double nT,double nY); /* The function y'    */
double  funcTY2(double nT,double nY); /* The function y''   */
double  funcTY3(double nT,double nY); /* The function y'''  */
double  funcTY4(double nT,double nY); /* The function y(4)  */

int main(int argc, char* argv[])
{
	int nStatus = 0;
	int  i;
	double*  pTPoints = NULL;
	double*  pYPoints = NULL;
	int      nInterval;
	double   nLowerLimit,nUpperLimit, nInitYValue;
	FuncTY   funcTY[4];

	funcTY[0] = funcTY1; funcTY[1] = funcTY2; funcTY[2] = funcTY3;	funcTY[3] = funcTY4;

	printf("\n ***  Taylor's Method of Order 4 *** \n");
	printf("\n y'   =  (t - y)/2        \n");
	printf("\n y''  =  (2 - t + y)/ 4   \n");
	printf("\n y''' =  (-2 + t - y)/ 8  \n");
	printf("\n y(4) =  (2 - t + y)/ 16  \n\n");

	/*  This is the input stage */
	printf(" Enter the lower limit: ");
	scanf("%lf",&nLowerLimit);	fflush(stdin);
	printf(" Enter the upper limit: ");
	scanf("%lf",&nUpperLimit);	fflush(stdin);

	/*  Ask for the interval*/
	do{
		printf(" Enter the interval M  [ > 0]: ");
		scanf("%d",&nInterval);	fflush(stdin);
	}while(nInterval <= 0);

	/*  Ask for the initial value y(0)*/
	printf(" Enter the initial value y(0): ");
	scanf("%lf",&nInitYValue);	fflush(stdin);

	pTPoints = (double*) malloc((nInterval + 1) * sizeof(pTPoints[0]));
	pYPoints = (double*) malloc((nInterval + 1) * sizeof(pYPoints[0]));

	if(!pTPoints || !pYPoints)
		nStatus = -1;

	if(nStatus == 0)
	{
		computeTaylorO4(nLowerLimit,nUpperLimit,nInitYValue,nInterval,funcTY,pTPoints,pYPoints);

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
	if(pTPoints) free(pTPoints);
	if(pYPoints) free(pYPoints);
	printf("\nPress any key to continue....");
	getch();
	return 0;
}

/* Evaluates the function y'  */
double  funcTY1(double nT,double nY)
{	return ((nT - nY) / 2); }

/* Evaluates the function y'' */
double  funcTY2(double nT,double nY)
{	return ((2 - nT + nY)/4); }

/* Evaluates the function y'''*/
double  funcTY3(double nT,double nY)
{	return ((-2 + nT - nY) / 8); }

/* Evaluates the function y(4) */
double  funcTY4(double nT,double nY)
{	return ((2 - nT + nY)/16); }

