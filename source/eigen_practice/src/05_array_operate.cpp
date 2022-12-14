#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc ,char*argv[])
{
    Eigen::ArrayXXf a(3, 3);
    Eigen::ArrayXXf b(3, 3);

    a << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    
    b << 1, 2, 3,
        1, 2, 3,
        1, 2, 3;
    
    std::cout << "a + b = " << std::endl << a + b << std::endl << std::endl;
    std::cout << "a - 2 = " << std::endl << a - 2 << std::endl;
    std::cout << "a * b = " << std::endl << a * b << std::endl;
    std::cout << "a / b = " << std::endl << a / b << std::endl;

    return 0;
}