// Matrix.tpp
#ifndef MATRIX_TPP
#define MATRIX_TPP

#include <iostream>
#include <stdexcept>

// Constructor
template <typename T>
Matrix<T>::Matrix(size_t r, size_t c, T fill) {
    rows = r;
    cols = c;
    data = std::vector<std::vector<T>>(r, std::vector<T>(c, fill));
}

// Initializer list constructor
template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> vals) {
    rows = vals.size();
    cols = vals.begin()->size();

    for (auto& row : vals) {
        data.push_back(std::vector<T>(row));
    }
}

// Element access
template <typename T>
T& Matrix<T>::operator()(size_t r, size_t c) {
    return data[r][c];
}

template <typename T>
const T& Matrix<T>::operator()(size_t r, size_t c) const {
    return data[r][c];
}

template <typename T>
size_t Matrix<T>::numRows() const {
    return rows;
}

template <typename T>
size_t Matrix<T>::numCols() const {
    return cols;
}

// Matrix addition
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    Matrix<T> result(rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = data[i][j] + other(i, j);
        }
    }
    return result;
}

// Matrix multiplication
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    Matrix<T> result(rows, other.numCols(), 0);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < other.numCols(); j++) {
            for (size_t k = 0; k < cols; k++) {
                result(i, j) += data[i][k] * other(k, j);
            }
        }
    }

    return result;
}

// Transpose
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> t(cols, rows);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            t(j, i) = data[i][j];
        }
    }

    return t;
}

// Print
template <typename T>
void Matrix<T>::print() const {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

#endif
