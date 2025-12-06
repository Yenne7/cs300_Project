#ifndef TENSOR3D_CPP
#define TENSOR3D_CPP

#include <stdexcept>

template <typename T>
Tensor3D<T>::Tensor3D(size_t d, size_t r, size_t c, T init) {
    depth = d;
    rows = r;
    cols = c;
    
    data.resize(d);
    for (size_t k = 0; k < d; k++) {
        data[k].resize(r);
        for (size_t i = 0; i < r; i++) {
            data[k][i].resize(c, init);
        }
    }
}

template <typename T>
Tensor3D<T>::Tensor3D(
    std::initializer_list<std::initializer_list<std::initializer_list<T>>> vals) {
    
    depth = vals.size();
    rows = vals.begin()->size();
    cols = vals.begin()->begin()->size();
    
    for (auto& channel : vals) {
        data.push_back(std::vector<std::vector<T>>());
        for (auto& row : channel) {
            data.back().push_back(std::vector<T>(row));
        }
    }
}

template <typename T>
T& Tensor3D<T>::operator()(size_t k, size_t i, size_t j) {
    return data[k][i][j];
}

template <typename T>
const T& Tensor3D<T>::operator()(size_t k, size_t i, size_t j) const {
    return data[k][i][j];
}

template <typename T>
Tensor3D<T> Tensor3D<T>::operator+(const Tensor3D<T>& other) const {
    Tensor3D<T> result(depth, rows, cols);
    
    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result(k, i, j) = data[k][i][j] + other(k, i, j);
            }
        }
    }
    
    return result;
}

template <typename T>
Tensor3D<T> Tensor3D<T>::elemwiseMultiply(const Tensor3D<T>& other) const {
    Tensor3D<T> result(depth, rows, cols);
    
    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result(k, i, j) = data[k][i][j] * other(k, i, j);
            }
        }
    }
    
    return result;
}

template <typename T>
Matrix<T> Tensor3D<T>::slice(size_t k) const {
    Matrix<T> result(rows, cols);
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(i, j) = data[k][i][j];
        }
    }
    
    return result;
}

template <typename T>
void Tensor3D<T>::reshape(size_t newD, size_t newR, size_t newC) {
    if (depth * rows * cols != newD * newR * newC) {
        throw std::invalid_argument("Total elements must match");
    }
    
    std::vector<T> flat;
    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                flat.push_back(data[k][i][j]);
            }
        }
    }
    
    data.clear();
    data.resize(newD);
    for (size_t k = 0; k < newD; k++) {
        data[k].resize(newR);
        for (size_t i = 0; i < newR; i++) {
            data[k][i].resize(newC);
        }
    }
    
    depth = newD;
    rows = newR;
    cols = newC;
    
    size_t idx = 0;
    for (size_t k = 0; k < newD; k++) {
        for (size_t i = 0; i < newR; i++) {
            for (size_t j = 0; j < newC; j++) {
                data[k][i][j] = flat[idx++];
            }
        }
    }
}

template <typename T>
Tensor3D<T> Tensor3D<T>::operator*(const Matrix<T>& M) const {
    Tensor3D<T> result(depth, rows, M.numCols(), 0);
    
    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < M.numCols(); j++) {
                for (size_t x = 0; x < cols; x++) {
                    result(k, i, j) += data[k][i][x] * M(x, j);
                }
            }
        }
    }
    
    return result;
}

#endif