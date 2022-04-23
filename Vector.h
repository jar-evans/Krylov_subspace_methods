#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

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

    inline T& operator[](int i) const
    {
        return data[i];
    }

    inline T operator()(int i) const
    {
        return data[i];
    }

    template <typename U>
    Vector<typename std::common_type<T, U>::type> operator/(const U scal)
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] / scal;
        return v;
    }

    template <typename U>
    Vector<typename std::common_type<T, U>::type> operator*(const U scal)
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] * scal;
        return v;
    }

    template <typename U>
    Vector<typename std::common_type<T, U>::type> operator+(const Vector<U> &other)
    {
        Vector<typename std::common_type<T, U>::type> v(n);
        for (int i = 0; i < n; i++)
            v[i] = data[i] + other[i];
        return v;
    }

    template <typename U>
    Vector<typename std::common_type<T, U>::type> operator-(const Vector<U> &other)
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

#endif
