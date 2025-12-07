#include <iostream>
#include "Tensor3D.h"

using namespace std;

int main() {
    cout << "== Matrix quick tests ==" << endl;

    Matrix<int> m1(2, 2, 7);
    cout << "m1(0,0) = " << m1(0,0) << endl;

    Matrix<int> m2 = { {1, 2}, {3, 4} };
    Matrix<int> m3 = { {5, 6}, {7, 8} };

    Matrix<int> sum = m2 + m3;
    cout << "sum(0,0) = " << sum(0,0) << endl;
    cout << "sum(1,1) = " << sum(1,1) << endl;

    Matrix<int> prod = m2 * m3;
    cout << "prod(0,0) = " << prod(0,0) << endl;
    cout << "prod(1,1) = " << prod(1,1) << endl;

    cout << "\n== Tensor3D quick tests ==" << endl;

    Tensor3D<int> t1(2, 2, 2, 1);
    t1(0,0,1) = 3;
    cout << "t1(0,0,0) = " << t1(0,0,0) << ", t1(0,0,1) = " << t1(0,0,1) << endl;

    Tensor3D<int> t2 = {
        { {1, 2}, {3, 4} },
        { {5, 6}, {7, 8} }
    };

    Tensor3D<int> t3 = t1 + t2;
    cout << "t3(0,0,0) = " << t3(0,0,0) << endl;
    cout << "t3(1,1,1) = " << t3(1,1,1) << endl;

    Matrix<int> eye = { {1, 0}, {0, 1} };
    Tensor3D<int> t4 = t2 * eye;
    cout << "t4(0,0,0) = " << t4(0,0,0) << endl;
    cout << "t4(1,1,1) = " << t4(1,1,1) << endl;

    Matrix<int> s0 = t2.slice(0);
    cout << "slice(0)(0,0) = " << s0(0,0) << endl;

    return 0;
}
