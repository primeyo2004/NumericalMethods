#include "LgrngApx.h"
/* Function name      : lagrangeApprox
* Description         : This is used to get the approximated value of 
*                       Y for a given input X.
* Parameter(s)        : 
*     nDegree         [in]  The degree of the polynomial.
*     xNodes[]        [in]  The node array containing the known 
*                           points of X. 
*                           (The size of this array must be nDegree + 1).
*     yNodes[]         [in]  The node array containing Y = f(x) values 
*                            corresponding each nodes in xNodes. 
*                           (The size of this array must be nDegree + 1).
*     nInputX         [in]  The independent variable X inorder to obtain
*                           Y = Pn(x).
* Return              :     
*    double               Returns the computed Y = Pn(x).
*/
double    
lagrangeApprox(int nDegree,double xNodes[],double yNodes[],double nInputX)
{
    double dblRet = 0;

    
    register int k;
    for(k = 0; k <= nDegree; k++)
    {
        /* This outer loop will be used to compute the summation
          of YkLn,k(x). 0 <= k <= Degree.
          ------------------------------------------------------    
        */

        double nLagCoef = 1;  /* Since we will compute for the products
                            we will start for an initial value of 1 */
        register int j;
        for(j = 0; j <= nDegree; j++)
        {
            /* This inner loop will be used to compute the product
              of Lj,k(x). 0 <= j <= Degree.
              ------------------------------------------------------    
            */

            if(j != k)   /* Skip the term when j == k */
            {
                /* Compute the product */
                nLagCoef *= ((nInputX - xNodes[j])/(xNodes[k] - xNodes[j]));
            }

        }

        dblRet += (yNodes[k] * nLagCoef);

        /* 
          ------------------------------------------------------    
        */
    }

    return dblRet;
}