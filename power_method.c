#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>


#define SIZE 3


int main() {

    double A[SIZE][SIZE], x[SIZE], y[SIZE];
    double start, end;
    double eps = 0.0000000001;
    double lambda = 0;
    double lambda0 = lambda + 2*eps;

    int i, j;
    int k = 0;
    int M = 100;

    for (i=0;i<SIZE;i++) {
        for (j=0;j<SIZE;j++) {
            x[j] = 1.0;
            y[j] = 0.0;
        }
    }

    A[0][0] = 1;
    A[0][1] = 1;
    A[0][2] = 1;
    A[1][0] = 1;
    A[1][1] = 11;
    A[1][2] = 1;
    A[2][0] = 1;
    A[2][1] = 1;
    A[2][2] = 1;



    start = omp_get_wtime();

    while ((k < M) && (fabs(lambda0 - lambda) > eps)) {

        lambda0 = lambda;
        
        #pragma omp parallel private(i, j) 
        {
        #pragma omp for schedule(static)
        for (j=0;j<SIZE;j++) {
            #pragma omp parallel shared(A, y, x) 
            {
            #pragma omp for schedule(static)
            for(i=0; i<SIZE;i++) {
                y[j] = y[j] + A[j][i]*x[i];
            }
            }
        }
        }

        lambda = 0;

        for (i = 0; i<SIZE;i++) {
            if (lambda < y[i]) {
            lambda = y[i];
            }
        }
        for (i=0;i<SIZE;i++) {
            x[i] = y[i]/lambda;
            y[i] = 0;
        }

        printf("Iteration %d: %f\n", k+1, lambda);
        k++;

    }

    if (k < M) {
        printf("\nCONVERGED IN %d ITERATIONS\n", k);
    }

    end = omp_get_wtime();

    printf("Wall clock time: %.20f\n",end - start);

    return 0;

}