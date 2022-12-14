#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main() {
    Matrix4f d;
    MatrixXd m(2, 5);
    m.resize(4, 3);
    std::cout << "The matrix m is of size "
              << m.rows() << "x" << m.cols() << std::endl;
    std::cout << "It has " << m.size() << " coefficients" << std::endl;
    VectorXd v(2);
    v.resize(5);
    std::cout << "The vector v is of size " << v.size() << std::endl;
    std::cout << "As a matrix, v is of size "
              << v.rows() << "x" << v.cols() << std::endl;
}

/*output:
The matrix m is of size 4x3
It has 12 coefficients
The vector v is of size 5
As a matrix, v is of size 5x1
*/