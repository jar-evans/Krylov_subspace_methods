#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 3

double power_method(double** A, double* x, double* y, double max_iter) {

    double start, end;
    double eps = 0.0000000001;
    double lambda = 0;
    double lambda0 = lambda + 2*eps;
    int k = 0;
    int M = 100;
    int i,j;

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

    return lambda;

}
