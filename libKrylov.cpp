#include <cmath>
#include <iostream>
#include <cassert>

#include "Vector.h"
#include "Matrix.h"

template <typename T, typename U>
typename std::common_type<T, U>::type
dot(const Vector<T> &lhs,
    const Vector<U> &rhs)
{
    typename std::common_type<T, U>::type sum = 0;

    for (auto i = 0; i < lhs.len(); i++)
        sum = sum + (lhs[i] * rhs[i]);
    return sum;
}
 
template <typename T, typename U>
auto mult(const Matrix<T> &lhs,
          const Vector<U> &rhs)
{
    Vector<typename std::common_type<T, U>::type> sum(lhs.cols());

    for (int i = 0; i < lhs.rows(); i++)
    {
        for (int j = 0; j < lhs.cols(); j++)
        {
            sum[i] = sum[i] + (lhs(i, j) * rhs[j]);
        }
    }
    return sum;
}

template <typename T>
Matrix<T> lanczos(const Matrix<T> A, int N)
{

    assert(A.rows() == A.cols());

    int n = A.rows();

    Vector<T> q_old(n);

    Vector<T> q(n);

    q[n - 1] = 1;

    Vector<T> r = q;
    Matrix<T> R(N - 1, N - 1);
    Matrix<int> I(n, n);
    I.identity();

    I.print();

    double b = 1;
    double a = 0;

    for (int i = 0; i < N; i++)
    {
        q = r / b;

        a = dot(q, mult(A, q));

        auto d = q_old * b;
        auto e = A - (I * a);
        auto f = mult(e, q);

        r = f - d;

        R(i, i) = a;

        b = r.norm();

        if (b < 1e-8)
            return R.resize(i);

        if (i < N - 1)
        {
            R(i, i + 1) = b;
            R(i + 1, i) = b;
        }

        q_old = q;
    }

    return R;
}

template <typename T>
Matrix<T> arnoldi(const Matrix<T> A, int N)
{

    assert(A.rows() == A.cols());

    int n = A.rows();

    Vector<T> q(n);
    q[n - 1] = 1;

    Vector<T> r = q;

    Matrix<T> H(N + 1, N);
    Matrix<T> Q(n, N + 1);

    for (int k = 0; k < n; k++)
    {
        Q(k, 0) = q[k];
    }

    double b = 1;

    for (int i = 0; i < N; i++)
    {

        r = mult(A, q);

        for (int j = 0; j < i + 1; j++)
        {

            for (int k = 0; k < n; k++)
            {
                q[k] = Q(k, j);
            }

            H(j, i) = dot(q, r);

            r = r - q * H(j, i);
        }

        b = r.norm();

        std::cout << b << std::endl;
        H(i + 1, i) = b;

        if (b < 1e-8)
        {
            // return Q.resize(n-1,i);
            return H;
        }

        for (int k = 0; k < n; k++)
        {
            Q(k, i + 1) = r[k] / b;
        }
    }

    return Q; //, H;
}

template <typename T, typename U>
typename std::common_type<T, U>::type
power(const Matrix<T> A, Vector<U> q_old, int N)
{
    Vector<typename std::common_type<T, U>::type> z(A.cols());
    auto q = q_old;

    typename std::common_type<T, U>::type lambda;
    typename std::common_type<T, U>::type lambda_old;

    lambda = 0;

    for (int k = 0; k < N; k++)
    {

        lambda_old = lambda;

        z = mult(A, q_old);
        q = z / z.norm();
        lambda = dot(q_old, z);
        q_old = q;

        if (fabs(lambda - lambda_old) < 1e-8) {
            return lambda;
        }
    }

    return lambda;
}