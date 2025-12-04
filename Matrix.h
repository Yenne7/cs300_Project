// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <initializer_list>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t r, size_t c, T fill = 0);
    Matrix(std::initializer_list<std::initializer_list<T>> vals);

    T& operator()(size_t r, size_t c);
    const T& operator()(size_t r, size_t c) const;

    size_t numRows() const;
    size_t numCols() const;

    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;

    Matrix<T> transpose() const;

    void print() const;
};

#include "Matrix.cpp"
#endif
