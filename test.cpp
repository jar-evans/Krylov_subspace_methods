#include <iostream>
#include "libKrylov.cpp"

int main()
{

    Matrix<double> A(3, 3);

    A(0, 0) = 12;
    A(1, 0) = 0;
    A(2, 0) = 0;
    A(0, 1) = 0;
    A(1, 1) = 2;
    A(2, 1) = 1;
    A(0, 2) = 0;
    A(1, 2) = 1;
    A(2, 2) = 2;

    Vector<double> b(3);
    b[0] = 1;
    b[1] = 1;
    b[2] = 1;

    double start = omp_get_wtime();
    auto a = power(A, b / b.norm(), 3);
    double end = omp_get_wtime();

    std::cout << a << " in " << end - start << " [s]" << std::endl;
}