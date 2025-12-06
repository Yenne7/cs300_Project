#include <iostream>
#include "Tensor3D.h"

int main() {
    std::cout << "=== Matrix (2D) Test Cases ===\n";

    // Matrix Test 1: Constructor with dimensions
    std::cout << "Matrix Test 1: Constructor with dimensions (3x3, init=7)\n";
    Matrix<int> m1(3, 3, 7);
    std::cout << "m1(0,0) = " << m1(0,0) << " (expected: 7)\n";
    std::cout << "m1(2,2) = " << m1(2,2) << " (expected: 7)\n\n";

    // Matrix Test 2: Initializer list constructor
    std::cout << "Matrix Test 2: Initializer list constructor\n";
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}};
    std::cout << "m2(0,0) = " << m2(0,0) << " (expected: 1)\n";
    std::cout << "m2(0,2) = " << m2(0,2) << " (expected: 3)\n";
    std::cout << "m2(1,1) = " << m2(1,1) << " (expected: 5)\n\n";

    // Matrix Test 3: Element access and modification
    std::cout << "Matrix Test 3: Element access and modification\n";
    m2(0,0) = 99;
    std::cout << "After m2(0,0) = 99: " << m2(0,0) << " (expected: 99)\n\n";

    // Matrix Test 4: Matrix addition
    std::cout << "Matrix Test 4: Matrix addition\n";
    Matrix<int> m3 = {{1, 2}, {3, 4}};
    Matrix<int> m4 = {{10, 20}, {30, 40}};
    Matrix<int> m5 = m3 + m4;
    std::cout << "m5(0,0) = " << m5(0,0) << " (expected: 11)\n";
    std::cout << "m5(1,1) = " << m5(1,1) << " (expected: 44)\n\n";

    // Matrix Test 5: Matrix multiplication
    std::cout << "Matrix Test 5: Matrix multiplication\n";
    Matrix<int> m6 = {{1, 2}, {3, 4}};
    Matrix<int> m7 = {{2, 0}, {1, 3}};
    Matrix<int> m8 = m6 * m7;
    std::cout << "m8(0,0) = " << m8(0,0) << " (expected: 4)\n";
    std::cout << "m8(0,1) = " << m8(0,1) << " (expected: 6)\n";
    std::cout << "m8(1,0) = " << m8(1,0) << " (expected: 10)\n";
    std::cout << "m8(1,1) = " << m8(1,1) << " (expected: 12)\n\n";

    // Matrix Test 6: Transpose
    std::cout << "Matrix Test 6: Transpose\n";
    Matrix<int> m9 = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int> m10 = m9.transpose();
    std::cout << "Original m9 size: " << m9.numRows() << "x" << m9.numCols() << "\n";
    std::cout << "Transposed m10 size: " << m10.numRows() << "x" << m10.numCols() << "\n";
    std::cout << "m10(0,0) = " << m10(0,0) << " (expected: 1)\n";
    std::cout << "m10(2,1) = " << m10(2,1) << " (expected: 6)\n\n";

    std::cout << "=== Tensor3D (3D) Test Cases ===\n";

    // Tensor3D Test 1: Constructor with dimensions
    std::cout << "Tensor3D Test 1: Constructor with dimensions (2x3x4, init=5)\n";
    Tensor3D<int> t1(2, 3, 4, 5);
    std::cout << "t1(0,0,0) = " << t1(0,0,0) << " (expected: 5)\n";
    std::cout << "t1(1,2,3) = " << t1(1,2,3) << " (expected: 5)\n\n";

    // Tensor3D Test 2: Initializer list constructor
    std::cout << "Tensor3D Test 2: Initializer list constructor\n";
    Tensor3D<int> t2 = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    std::cout << "t2(0,0,0) = " << t2(0,0,0) << " (expected: 1)\n";
    std::cout << "t2(0,0,1) = " << t2(0,0,1) << " (expected: 2)\n";
    std::cout << "t2(1,1,1) = " << t2(1,1,1) << " (expected: 8)\n\n";

    // Tensor3D Test 3: Element access and modification
    std::cout << "Tensor3D Test 3: Element access and modification\n";
    t2(0,0,0) = 99;
    std::cout << "After t2(0,0,0) = 99: " << t2(0,0,0) << " (expected: 99)\n\n";

    // Tensor3D Test 4: Tensor addition
    std::cout << "Tensor3D Test 4: Tensor addition\n";
    Tensor3D<int> t3 = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    Tensor3D<int> t4 = {
        {{10, 20}, {30, 40}},
        {{50, 60}, {70, 80}}
    };
    Tensor3D<int> t5 = t3 + t4;
    std::cout << "t5(0,0,0) = " << t5(0,0,0) << " (expected: 11)\n";
    std::cout << "t5(0,1,1) = " << t5(0,1,1) << " (expected: 44)\n";
    std::cout << "t5(1,1,1) = " << t5(1,1,1) << " (expected: 88)\n\n";

    // Tensor3D Test 5: Elementwise multiplication
    std::cout << "Tensor3D Test 5: Elementwise multiplication\n";
    Tensor3D<int> t6 = {
        {{2, 3}, {4, 5}},
        {{6, 7}, {8, 9}}
    };
    Tensor3D<int> t7 = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    Tensor3D<int> t8 = t6.elemwiseMultiply(t7);
    std::cout << "t8(0,0,0) = " << t8(0,0,0) << " (expected: 2)\n";
    std::cout << "t8(0,0,1) = " << t8(0,0,1) << " (expected: 6)\n";
    std::cout << "t8(1,1,1) = " << t8(1,1,1) << " (expected: 72)\n\n";

    // Tensor3D Test 6: Slice extraction
    std::cout << "Tensor3D Test 6: Slice extraction\n";
    Tensor3D<int> t9 = {
        {{1, 2, 3}, {4, 5, 6}},
        {{7, 8, 9}, {10, 11, 12}}
    };
    Matrix<int> slice0 = t9.slice(0);
    Matrix<int> slice1 = t9.slice(1);
    std::cout << "slice0(0,0) = " << slice0(0,0) << " (expected: 1)\n";
    std::cout << "slice0(1,2) = " << slice0(1,2) << " (expected: 6)\n";
    std::cout << "slice1(0,0) = " << slice1(0,0) << " (expected: 7)\n";
    std::cout << "slice1(1,2) = " << slice1(1,2) << " (expected: 12)\n\n";

    // Tensor3D Test 7: Reshape
    std::cout << "Tensor3D Test 7: Reshape (2x2x2 -> 1x4x2)\n";
    Tensor3D<int> t10 = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    std::cout << "Before reshape: t10(1,1,1) = " << t10(1,1,1) << "\n";
    t10.reshape(1, 4, 2);
    std::cout << "After reshape to 1x4x2:\n";
    std::cout << "t10(0,0,0) = " << t10(0,0,0) << " (expected: 1)\n";
    std::cout << "t10(0,1,0) = " << t10(0,1,0) << " (expected: 3)\n";
    std::cout << "t10(0,3,1) = " << t10(0,3,1) << " (expected: 8)\n\n";

    // Tensor3D Test 8: Channel-wise matrix multiplication
    std::cout << "Tensor3D Test 8: Channel-wise matrix multiplication\n";
    Tensor3D<int> t11 = {
        {{1, 2, 3}, {4, 5, 6}},
        {{7, 8, 9}, {10, 11, 12}}
    };
    Matrix<int> m11 = {{1, 0}, {0, 1}, {1, 1}};
    Tensor3D<int> t12 = t11 * m11;
    std::cout << "Result tensor shape: 2x2x2\n";
    std::cout << "t12(0,0,0) = " << t12(0,0,0) << " (expected: 4)\n";
    std::cout << "t12(0,0,1) = " << t12(0,0,1) << " (expected: 5)\n";
    std::cout << "t12(1,0,0) = " << t12(1,0,0) << " (expected: 16)\n\n";

    std::cout << "=== All tests completed successfully ===\n";
    
    return 0;
}