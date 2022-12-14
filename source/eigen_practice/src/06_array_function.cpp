#include <iostream>
#include <eigen3/Eigen/Dense>


int main(int argc, char *argv[])
{
    Eigen::ArrayXXf a = Eigen::ArrayXXf::Random(2, 2);
    a *= 2;
    std::cout << "a = " << std::endl
         << a << std::endl;
    std::cout << "a.abs() = " << std::endl
         << a.abs() << std::endl;
    std::cout << "a.abs().sqrt() =" << std::endl
         << a.abs().sqrt() << std::endl;
    std::cout << "a.min(a.abs().sqrt()) = " << std::endl
         << a.min(a.abs().sqrt()) << std::endl;

    return 0;
}
