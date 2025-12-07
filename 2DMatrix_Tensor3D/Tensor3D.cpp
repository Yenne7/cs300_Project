#ifndef TENSOR3D_CPP
#define TENSOR3D_CPP
#include <stdexcept>
using namespace std;


template <typename T>
Tensor3D<T>::Tensor3D(size_t d, size_t r, size_t c, T init) {
    depth = d;
    rows = r;
    cols = c;
    
    data.resize(depth);
    for (size_t k = 0; k < depth; k++) {
        data[k].resize(rows);
        for (size_t i = 0; i < rows; i++) {
            data[k][i].resize(cols, init);
        }
    }
}

template <typename T>
Tensor3D<T>::Tensor3D(
    initializer_list<initializer_list<initializer_list<T>>> vals) {
    
    depth = vals.size();
    if (depth == 0) {
        rows = 0;
        cols = 0;
        return;
    }

    rows = vals.begin()->size();
    if (rows == 0) {
        cols = 0;
    } else {
        cols = vals.begin()->begin()->size();
    }
    
    for (auto &channel : vals) {
        data.push_back(vector<vector<T>>());
        for (auto &row : channel) {
            data.back().push_back(vector<T>(row));
        }
    }
}

template <typename T>
T& Tensor3D<T>::operator()(size_t k, size_t i, size_t j) {
    if (k >= depth || i >= rows || j >= cols) {
        throw out_of_range("Tensor3D index out of range");
    }
    return data[k][i][j];
}

template <typename T>
const T& Tensor3D<T>::operator()(size_t k, size_t i, size_t j) const {
    if (k >= depth || i >= rows || j >= cols) {
        throw out_of_range("Tensor3D index out of range");
    }
    return data[k][i][j];
}

template <typename T>
Tensor3D<T> Tensor3D<T>::operator+(const Tensor3D<T>& other) const {
    if (depth != other.depth || rows != other.rows || cols != other.cols) {
        throw invalid_argument("Tensor3D sizes must match for +");
    }

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
    if (depth != other.depth || rows != other.rows || cols != other.cols) {
        throw invalid_argument("Tensor3D sizes must match for elemwiseMultiply");
    }

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
    if (k >= depth) {
        throw out_of_range("slice index out of range");
    }

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
        throw invalid_argument("Total elements must match in reshape");
    }
    
    vector<T> flat;
    flat.reserve(depth * rows * cols);

    for (size_t k = 0; k < depth; k++) {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                flat.push_back(data[k][i][j]);
            }
        }
    }
    
    data.clear();
    data.resize(newD);
    
    size_t idx = 0;
    for (size_t k = 0; k < newD; k++) {
        data[k].resize(newR);
        for (size_t i = 0; i < newR; i++) {
            data[k][i].resize(newC);
            for (size_t j = 0; j < newC; j++) {
                data[k][i][j] = flat[idx++];
            }
        }
    }
    
    depth = newD;
    rows = newR;
    cols = newC;
}

template <typename T>
Tensor3D<T> Tensor3D<T>::operator*(const Matrix<T>& M) const {
    if (cols != M.numRows()) {
        throw invalid_argument("Tensor3D * Matrix size mismatch");
    }

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
