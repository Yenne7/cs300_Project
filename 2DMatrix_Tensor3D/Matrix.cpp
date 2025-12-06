#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <stdexcept>

template <typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init) {
    rows = r;
    cols = c;
    
    data.resize(r);
    for (size_t i = 0; i < r; i++) {
        data[i].resize(c, init);
    }
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> vals) {
    rows = vals.size();
    cols = vals.begin()->size();
    
    for (auto& row : vals) {
        data.push_back(std::vector<T>(row));
    }
}

template <typename T>
T& Matrix<T>::operator()(size_t i, size_t j) {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[i][j];
}

template <typename T>
const T& Matrix<T>::operator()(size_t i, size_t j) const {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[i][j];
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix<T> result(rows, cols);
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = data[i][j] + other(i, j);
        }
    }
    
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    
    Matrix<T> result(rows, other.cols, 0);
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < other.cols; j++) {
            for (size_t k = 0; k < cols; k++) {
                result(i, j) += data[i][k] * other(k, j);
            }
        }
    }
    
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols, rows);
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(j, i) = data[i][j];
        }
    }
    
    return result;
}

#endif