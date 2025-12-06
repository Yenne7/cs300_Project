#ifndef TENSOR3D_H
#define TENSOR3D_H

#include <vector>
#include <initializer_list>
#include "Matrix.h"

template <typename T>
class Tensor3D {
private:
    std::vector<std::vector<std::vector<T>>> data;
    size_t depth, rows, cols;

public:
    Tensor3D(size_t d, size_t r, size_t c, T init = 0);
    Tensor3D(std::initializer_list<std::initializer_list<std::initializer_list<T>>> vals);
    
    T& operator()(size_t k, size_t i, size_t j);
    const T& operator()(size_t k, size_t i, size_t j) const;
    
    Tensor3D<T> operator+(const Tensor3D<T>& other) const;
    Tensor3D<T> elemwiseMultiply(const Tensor3D<T>& other) const;
    Matrix<T> slice(size_t k) const;
    void reshape(size_t newD, size_t newR, size_t newC);
    Tensor3D<T> operator*(const Matrix<T>& M) const;
};

#include "Tensor3D.cpp"
#endif