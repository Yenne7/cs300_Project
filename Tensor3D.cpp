// Tensor3D.tpp
#ifndef TENSOR3D_CPP
#define TENSOR3D_CPP

#include <stdexcept>

// Simple constructor
template <typename T>
Tensor3D<T>::Tensor3D(size_t d, size_t r, size_t c, T fill) {
    depth = d;
    rows = r;
    cols = c;

    data = std::vector<std::vector<std::vector<T>>>(
        d,
        std::vector<std::vector<T>>(r, std::vector<T>(c, fill))
    );
}

// Initializer list constructor
template <typename T>
Tensor3D<T>::Tensor3D(
    std::initializer_list<std::initializer_list<std::initializer_list<T>>> vals) {

    depth = vals.size();
    rows = vals.begin()->size();
    cols = vals.begin()->begin()->size();

    for (auto& mat : vals) {
        data.push_back(std::vector<std::vector<T>>());
        for (auto& row : mat) {
            data.back().push_back(std::vector<T>(row));
        }
    }
}

// Element access
template <typename T>
T& Tensor3D<T>::operator()(size_t k, size_t r, size_t c) {
    return data[k][r][c];
}

template <typename T>
const T& Tensor3D<T>::operator()(size_t k, size_t r, size_t c) const {
    return data[k][r][c];
}

// Tensor addition
template <typename T>
Tensor3D<T> Tensor3D<T>::operator+(const Tensor3D<T>& other) const {
    Tensor3D<T> out(depth, rows, cols, 0);

    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                out(k, i, j) = data[k][i][j] + other(k, i, j);
            }
        }
    }

    return out;
}

// Elementwise multiply
template <typename T>
Tensor3D<T> Tensor3D<T>::elemwiseMultiply(const Tensor3D<T>& other) const {
    Tensor3D<T> out(depth, rows, cols);

    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                out(k, i, j) = data[k][i][j] * other(k, i, j);
            }
        }
    }

    return out;
}

// Slice
template <typename T>
Matrix<T> Tensor3D<T>::slice(size_t k) const {
    Matrix<T> m(rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m(i, j) = data[k][i][j];
        }
    }

    return m;
}

// Reshape
template <typename T>
void Tensor3D<T>::reshape(size_t newD, size_t newR, size_t newC) {
    std::vector<T> flat;

    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                flat.push_back(data[k][i][j]);
            }
        }
    }

    size_t newSize = newD * newR * newC;

    if (flat.size() != newSize) {
        throw std::invalid_argument("Total elements must match");
    }

    data = std::vector<std::vector<std::vector<T>>>(
        newD,
        std::vector<std::vector<T>>(newR, std::vector<T>(newC))
    );

    depth = newD;
    rows = newR;
    cols = newC;

    size_t index = 0;
    for (size_t k = 0; k < newD; k++) {
        for (size_t i = 0; i < newR; i++) {
            for (size_t j = 0; j < newC; j++) {
                data[k][i][j] = flat[index++];
            }
        }
    }
}

// Tensor × matrix
template <typename T>
Tensor3D<T> Tensor3D<T>::operator*(const Matrix<T>& m) const {
    Tensor3D<T> out(depth, rows, m.numCols(), 0);

    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < m.numCols(); j++) {
                for (size_t x = 0; x < cols; x++) {
                    out(k, i, j) += data[k][i][x] * m(x, j);
                }
            }
        }
    }

    return out;
}

#endif
