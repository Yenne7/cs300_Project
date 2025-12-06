
#ifndef TENSOR3D_H
#define TENSOR3D_H

#include <vector>
#include <initializer_list>
#include "Matrix.h"

template <typename T>
class Tensor3D {
private:
    std::vector<std::vector<std::vector<T>>> data;
    size_t depth;
    size_t rows;
    size_t cols;

public:
    Tensor3D(size_t d, size_t r, size_t c, T fill = 0);
    Tensor3D(std::initializer_list<std::initializer_list<std::initializer_list<T>>> vals);

    T& operator()(size_t k, size_t r, size_t c);
    const T& operator()(size_t k, size_t r, size_t c) const;

    Tensor3D<T> operator+(const Tensor3D<T>& other) const;

    Tensor3D<T> elemwiseMultiply(const Tensor3D<T>& other) const;

    Matrix<T> slice(size_t k) const;

    void reshape(size_t newD, size_t newR, size_t newC);

    Tensor3D<T> operator*(const Matrix<T>& m) const;
};

#include "Tensor3D.cpp"
#endif
