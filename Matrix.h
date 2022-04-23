#ifndef MATRIX_H
#define MATRIX_H

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

#endif