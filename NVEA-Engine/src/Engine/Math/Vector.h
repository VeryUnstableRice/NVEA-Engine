#ifndef Vector_Header
#define Vector_Header
#include <algorithm>
#include <cassert>

template<typename T, unsigned char size>
class SVector
{
    T Element[size];
public:
    T& operator[](int i) const
    {
        assert(i >= 0 && i < size);
        return Element[i];
    }
};

template<typename T>
class SVector<T, 2>
{
public:
    union { T x, r; };
    union { T y, g; };
    T& operator[](int i) const
    {
        assert(i >= 0 && i < size);
        switch(i)
        {
        case 0: return x;
        case 1: return y;
        }
    }
};

template<typename T>
class SVector<T, 3>
{
public:
    union { T x, r; };
    union { T y, g; };
    union { T z, b; };
    T& operator[](int i) const
    {
        assert(i >= 0 && i < size);
        switch(i)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        }
    }
};

template<typename T>
class SVector<T, 4>
{
public:
    union { T x, r; };
    union { T y, g; };
    union { T z, b; };
    union { T w, a; };
    T& operator[](int i) const
    {
        assert(i >= 0 && i < size);
        switch(i)
        {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        }
    }
};

template<typename T, unsigned char size>
SVector<T, size> operator-(const SVector<T, size>& A)
{
    SVector<T, size> output = A;
    for(int i = size-1; i >= 0;--i) output[i] = -output[i];
    return std::move(output);
}

template<typename T, unsigned char size>
SVector<T, size>& operator=(SVector<T, size>& A, const SVector<T, size>& B)
{
    for(int i = size-1; i >= 0;--i) A[i] = B[i];
    return A;
}

template<typename T, unsigned char size>
SVector<T, size> operator+(const SVector<T, size>& A, const SVector<T, size>& B)
{
    SVector<T, size> output = A;
    for(int i = size-1; i >= 0;--i) output[i] += B[i];
    return std::move(output);
}

template<typename T, unsigned char size>
SVector<T, size> operator-(const SVector<T, size>& A, const SVector<T, size>& B)
{
    return A + (-B);
}

template<typename T, unsigned char size>
SVector<T, size> operator*(const SVector<T, size>& A, const SVector<T, size>& B)
{
    SVector<T, size> output = A;
    for(int i = size-1; i >= 0;--i) output[i] *= B[i];
    return std::move(output);
}

template<typename T, unsigned char size>
SVector<T, size>& operator+=(SVector<T, size>& A, const SVector<T, size>& B)
{
    return A = A + B;
}

template<typename T, unsigned char size>
SVector<T, size>& operator-=(SVector<T, size>& A, const SVector<T, size>& B)
{
    return A = A - B;
}

template<typename T, unsigned char size>
SVector<T, size> operator*=(const SVector<T, size>& A, const SVector<T, size>& B)
{
    return A = A * B;;
}


#endif
