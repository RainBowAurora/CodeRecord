#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc, char *argv[])
{
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(3, 3);
    m = (m + Eigen::MatrixXd::Constant(3, 3, 1.2)) * 50;
    
    std::cout << "m = \n" << m << std::endl;

    Eigen::VectorXd v(3);
    v << 1, 2, 3;
    
    std::cout << "m*v= \n" << m * v << std::endl;

    return 0;
}

/*output:
m = 
94.0188  89.844 43.5223
49.4383 101.165  86.823
88.3099 29.7551 37.7775
m*v= 
404.274
512.237
261.153
*/