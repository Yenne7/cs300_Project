#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <initializer_list>
using namespace std;


template <typename T>
class Matrix {
private:
    vector<vector<T>> data;
    size_t rows, cols;

public:
    Matrix(size_t r, size_t c, T init = 0);
    Matrix(initializer_list<initializer_list<T>> vals);

    T& operator()(size_t i, size_t j);
    const T& operator()(size_t i, size_t j) const;

    size_t numRows() const { return rows; }
    size_t numCols() const { return cols; }

    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> transpose() const;
};

#include "Matrix.cpp"

#endif
