#include <stdio.h>
#include <conio.h>
#include "DirichletFunc.h"


double  fFunc1(int i,double H);
double  fFunc2(int i,double H);
double  fFunc3(int i,double H);
double  fFunc4(int i,double H);

int main(int argc, char* argv[])
{
    double grid[50][50];
    
    double wid_A, ht_B;             /* in : Width and height of Rectangle  */
    double space_H;                 /* The grid spacing */
    int xdim_N, ydim_M;             /* dx and dy  */
	double initVal;                 /* The initial value */ 
    int i,j;
	FUNCF   arrFunc[4];             /* The array of function that will hold F1-F4 */
    
    printf("\n  ***  Dirichlet Method for Laplace's Equation *** \n\n");

    /*  Ask input from user */
    printf("Please enter rectangular grid width  A   : ");  
    scanf("%lf",&wid_A);     fflush(stdin);
    printf("Please enter rectangular grid height B   : ");  
    scanf("%lf",&ht_B);      fflush(stdin);
    printf("Please grid spacing H: ");  
	scanf("%lf",&space_H);  fflush(stdin);
    printf("Please enter grid x dimension N: ");  
    scanf("%d",&xdim_N);  fflush(stdin);
    printf("Please enter grid y dimension M: ");  
    scanf("%d",&ydim_M);  fflush(stdin);
    printf("Please initial value for interior grid: ");  
	scanf("%lf",&initVal);  fflush(stdin);

	arrFunc[0] = fFunc1;
	arrFunc[1] = fFunc2;
	arrFunc[2] = fFunc3;
	arrFunc[3] = fFunc4;


    /* Compute the Dirichlet*/
    computeDirichlet(wid_A,ht_B,space_H,xdim_N,ydim_M,initVal,arrFunc,&grid[0][0],50);

    /* Display the output */
    i = 1;
    printf("\n================================================================\n");
    do{
        int nRow;
        for (nRow = 0; (nRow + i) <= xdim_N && nRow < 4; nRow++ )
                printf("   x[%d]  \t",(nRow + i));
        printf("\n----------------------------------------------------------------\n");

        for ( j = 1; j <= ydim_M; j++ )
        {
            for (nRow = 0; (nRow + i) <= xdim_N && nRow < 4; nRow++ )
                printf("%2.6lf\t", GRID(&grid[0][0],(nRow + i),j,50));

            printf("\n");
        }

        i+=4;
        printf("\n================================================================\n");

    }while(i <= xdim_N);


    printf("\nPress any key to continue..");
    getch();

    return 0;
}


double  fFunc1(int i,double H)
{
	/* Ignore the i and H */
	return 180;
}

double  fFunc2(int i,double H)
{
	/* Ignore the i and H */
	return 20;
}

double  fFunc3(int i,double H)
{
	/* Ignore the i and H */
	return 80;
}

double  fFunc4(int i,double H)
{
	/* Ignore the i and H */
	return 0;
}


