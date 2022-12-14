#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc, char *argv[])
{
    Eigen::Array44f a1, a2;
    Eigen::Matrix4f m1, m2;
    m1 = a1 * a2;           // coeffwise乘积，从数组到矩阵的隐式转换。
    a1 = m1 * m2;           //矩阵乘积，从矩阵到数组的隐式转换。
    a2 = a1 + m1.array();   //禁止混合数组和矩阵，必须显式转换以后才可以相加
    m2 = a1.matrix() + m1;  //需要显式转换。
    Eigen::ArrayWrapper<Eigen::Matrix4f> m2a(m1);
    Eigen::MatrixWrapper<Eigen::Array44f> a2m(a1);
    std::cout << "a1: " << std::endl << a1 << std::endl;
    std::cout << "a2: " << std::endl << a2 << std::endl;
    std::cout << "m1: " << std::endl << m1 << std::endl;
    std::cout << "m2: " << std::endl << m2 << std::endl;

    return 0;
}

/*output:
a1: 
-6.50428e+13 -3.13006e-18 -4.26508e+28 -3.12221e-18
           0            0            0            0
-6.13256e+13 -2.70556e-18 -4.02133e+28 -2.69878e-18
           0            0            0            0
a2: 
 1.35439e+19  1.35534e+19 -4.26508e+28  1.15901e+19
           0            0            0            0
 1.27699e+19  1.29722e+19 -4.02133e+28  9.94454e+18
           0            0            0            0
m1: 
1.35439e+19 1.35534e+19 1.35456e+19 1.15901e+19
          0           0           0           0
1.27699e+19 1.29722e+19 1.17085e+19 9.94454e+18
          0           0           0           0
m2: 
 1.35439e+19  1.35534e+19 -4.26508e+28  1.15901e+19
           0            0            0            0
 1.27699e+19  1.29722e+19 -4.02133e+28  9.94454e+18

*/