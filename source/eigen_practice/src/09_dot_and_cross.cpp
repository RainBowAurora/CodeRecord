#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc, char*argv[])
{
    Eigen::Vector3d v(1, 2, 3);
    Eigen::Vector3d w(0, 1, 2);

    std::cout << "Dot product: " << v.dot(w) << std::endl;
    double dp = v.adjoint()*w; // automatic conversion of the inner product to a scalar
    std::cout << "Dot product via a matrix product: " << dp << std::endl;
    std::cout << "Cross product:\n" << v.cross(w) << std::endl;
    return 0;
}

/*output:
Dot product: 8
Dot product via a matrix product: 8
Cross product:
 1
-2
 1
*/