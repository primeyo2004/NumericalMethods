#include <stdio.h>
#include <conio.h>
#include "FiniteDiffFuncW.h"

double  gFunc(int i,double H);
double  fFunc(int i,double H);

int main(int argc, char* argv[])
{
    double grid[50][50];
    double wid_A, ht_B;          /* in : Width and height of Rectangle  */
    double cons_C;               /* in : Wave equation const.           */
    int xdim_N, ydim_M;          /* dx and dy  */
    int i,j;
   
    printf("\n  ***  Finite-Difference Solution for Wave Equation *** \n\n");
    /*  Ask input from user */
    printf("Please enter rectangular grid width  A: ");  
    scanf("%lf",&wid_A);     fflush(stdin);
    printf("Please enter rectangular grid height B: ");  
    scanf("%lf",&ht_B);      fflush(stdin);
    printf("Please enter wave eq. constant C: ");  
    scanf("%lf",&cons_C);  fflush(stdin);
    printf("Please enter grid x dimension N: ");  
    scanf("%d",&xdim_N);  fflush(stdin);
    printf("Please enter grid y dimension M: ");  
    scanf("%d",&ydim_M);  fflush(stdin);

    /* Compute the finite difference */
    computeFiniteDiffWave(wid_A,ht_B,cons_C,xdim_N,ydim_M,gFunc,fFunc,&grid[0][0],50);

    /* Display the output */
    i = 1;
    printf("\n================================================================\n");
    do{
        int nRow;
        printf(" t[j] \t");
        for (nRow = 0; (nRow + i) <= xdim_N && nRow < 4; nRow++ )
                printf("   x[%d]  \t",(nRow + i));
        printf("\n----------------------------------------------------------------\n");

        for ( j = 1; j <= ydim_M; j++ )
        {
            printf("%2.4lf\t", (ht_B / ( ydim_M - 1 )) * (j - 1));

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

double  gFunc(int i,double H)
{   /* g(x) = 0 */   return 0; }

double  fFunc(int i,double H)
{
    double arg;
    arg = H * (i - 1);
    return ( sin ( 3.1415926 * arg) + sin ( 2 * 3.1415926 * arg));
}


