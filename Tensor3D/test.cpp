#include <iostream>
#include "Tensor3D.h"
using namespace std;

// Simple test helper
void printResult(string name, bool ok) {
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << endl;
}

// BASIC Matrix tests
void testBasicMatrix() {
    cout << "\n=== Basic Matrix Tests ===" << endl;

    // Test 1: Create a Matrix with rows, cols, and a fill value
    Matrix<int> m1(2, 3, 7); // 2 rows, 3 cols, every element = 7
    bool t1 = (m1.numRows() == 2 && m1.numCols() == 3 &&
               m1(0, 0) == 7 && m1(1, 2) == 7);
    printResult("Matrix construction with fill value", t1);

    // Test 2: Change one value
    m1(1, 1) = 20;
    bool t2 = (m1(1, 1) == 20);
    printResult("Matrix set element", t2);

    // Test 3: Add two matrices
    Matrix<int> m2(2, 3, 1);  
    Matrix<int> m3 = m1 + m2;
    bool t3 = (m3(0, 0) == 8 &&
               m3(1, 1) == 21); 
    printResult("Matrix addition", t3);
}

// BASIC Tensor3D tests
void testBasicTensor3D() {
    cout << "\n=== Basic Tensor3D Tests ===" << endl;

    // Test 1: Construct Tensor3D with fill
    Tensor3D<int> t(2, 2, 2, 5);
    bool t1 = (t(0, 0, 0) == 5 &&
               t(1, 1, 1) == 5);
    printResult("Tensor3D construction with fill value", t1);

    // Test 2: Change a value
    t(1, 0, 1) = 99;
    bool t2 = (t(1, 0, 1) == 99);
    printResult("Tensor3D set element", t2);

    // Test 3: Add two tensors
    Tensor3D<int> t2ten(2, 2, 2, 1);
    Tensor3D<int> t3 = t + t2ten;

    bool t3ok = (t3(0, 0, 0) == 6 &&
                 t3(1, 0, 1) == 100);
    printResult("Tensor3D addition", t3ok);

    // Test 4: Slice returns a Matrix
    Tensor3D<int> ts(2, 2, 3, 4); // everything is 4
    Matrix<int> slice = ts.slice(1); // get the middle layer

    bool t4 = (slice.numRows() == 2 &&
               slice.numCols() == 3 &&
               slice(0, 0) == 4 &&
               slice(1, 2) == 4);
    printResult("Tensor3D slice", t4);
}

int main() {
    testBasicMatrix();
    testBasicTensor3D();
    return 0;
}
