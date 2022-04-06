#include <iostream>
#include <cmath>
#include <cassert>

template <typename T>
class Vector
{

public:
    Vector(int n)
        : n(n),
          data(new T[n])
    {
        for (int i = 0; i < n; i++)
        {
            data[i] = 0;
        }
    }

    Vector(const Vector &other)
        : Vector(other.len())
    {
        for (auto i = 0; i < other.len(); i++)
            data[i] = other.data[i];
    }

    double norm() const
    {
        double norm = 0;
        for (int i = 0; i < n; i++)
        {
            norm += data[i] * data[i];
        }
        return sqrt(norm);
    }

    inline T &operator[](int i) const
    {
        return data[i];
    }

    inline T operator()(int i) const
    {
        return data[i];
    }

    template <typename U>
    auto operator/(const U scal) const
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] / scal;
        return v;
    }

    template <typename U>
    auto operator*(const U scal) const
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] * scal;
        return v;
    }

    template <typename U>
    auto operator+(const Vector<U> &other) const
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] + other[i];
        return v;
    }

    template <typename U>
    auto operator-(const Vector<U> &other) const
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] - other[i];
        return v;
    }

    void print()
    {
        std::cout << "[";
        for (int i = 0; i < n; i++)
        {
            std::cout << data[i] << ",";
        }
        std::cout << "]\n";
    }

    int len() const
    {
        return n;
    }

private:
    int n;
    T *data;
};

template <typename T>
class Matrix
{
public:
    Matrix(int n, int m)
        : n(n),
          m(m),
          data(new T[n * m])
    {
    }

    inline T &operator()(int i, int j)
    {
        return data[i * m + j];
    }

    inline T operator()(int i, int j) const
    {
        return data[i * m + j];
    }

    template <typename U>
    auto operator*(const U scal) const
    {
        Matrix<typename std::common_type<T, U>::type> v(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                v(i, j) = data[i * m + j] * scal;
        return v;
    }

    template <typename U>
    auto operator-(const Matrix<U> &other) const
    {
        Matrix<typename std::common_type<T, U>::type> v(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                v(i, j) = data[i * m + j] - other(i, j);
        return v;
    }

    auto resize(int i, int j) const
    {
        Matrix<T> v(i + 1, j + 1);

        for (int c = 0; c < i + 1; c++)
            for (int k = 0; k < j + 1; k++)
                v(c, k) = data[c * m + k];
        return v;
    }

    auto resize(int i) const
    {
        Matrix<T> v(i + 1, i + 1);

        for (int j = 0; j < i + 1; j++)
            for (int k = 0; k < i + 1; k++)
                v(j, k) = data[j * m + k];
        return v;
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cout << data[i * m + j] << ",";
            }
            std::cout << "\n";
        }
    }

    void identity()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == j)
                {
                    data[i * m + j] = 1;
                }
                else
                {
                    data[i * m + j] = 0;
                }
            }
        }
    }

    int rows() const
    {
        return n;
    }

    int cols() const
    {
        return m;
    }

protected:
    int n;
    int m;
    T *data;
};

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

    Matrix<T> H(N+1, N);
    Matrix<T> Q(n, N+1);

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
            Q(k, i+1) = r[k] / b;
        }


    }

    return Q;//, H;
}

int main()
{

    Matrix<double> A(3, 3);

    A(0, 0) = 2;
    A(1, 0) = 0;
    A(2, 0) = 0;
    A(0, 1) = 0;
    A(1, 1) = 2;
    A(2, 1) = 1;
    A(0, 2) = 0;
    A(1, 2) = 1;
    A(2, 2) = 2;

    auto idk = arnoldi(A, 7);

    // idk.print();
}