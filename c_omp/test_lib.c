#include <stdio.h>
#include <stdlib.h>
#include "eig_pair.h"

#define SIZE 3

int main() {

    double** A;
    double* x, *y;
    int i, j;

    A = (double **)malloc(SIZE*sizeof(double *));
    x = (double *)malloc(SIZE*sizeof(double));
    y = (double *)malloc(SIZE*sizeof(double));
    if ((A == NULL) || (x == NULL) || (y == NULL)) {
        exit(1);
    }

    for(i = 0; i < SIZE; i++)
    {
        A[i] = (double *)malloc(SIZE*sizeof(double));
        if(A[i] == NULL)
            exit(1);
    }

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

    double lambda = power_method(A, x, y, 100);

    for (i=0;i<SIZE;i++) {
        free(A[i]);
    }
    free(A);

    return 0;

}
