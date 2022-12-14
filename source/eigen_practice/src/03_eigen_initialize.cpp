#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[]) {
    MatrixXd m0 = MatrixXd::Random(3, 3);           //随机初始化初始化的值在[-1,1]区间内,矩阵大小3X3
    MatrixXd m1 = MatrixXd::Constant(3, 3, 2.4);    //常量值初始化,矩阵里面的值全部为2.4 ,三个参数分别代表：行数，列数，常量值
    Matrix2d m2 = Matrix2d::Zero();                 //零初始化.矩阵里面的值全部为0
    Matrix3d m3 = Matrix3d::Ones();                 // 矩阵里面的值全部初始化为1
    Matrix4d m4 = Matrix4d::Identity();             //初始化为单位矩阵
    Matrix3d m5;                                    //逗号初始化
    m5 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "m0 =" << endl << m0 << endl;
    cout << "m1 =" << endl << m1 << endl;
    cout << "m2 =" << endl << m2 << endl;
    cout << "m3 =" << endl << m3 << endl;
    cout << "m4 =" << endl << m4 << endl;
    cout << "m5 =" << endl << m5 << endl;


    MatrixXf mat = MatrixXf::Ones(2, 3);
    std::cout << "before: " << endl << mat << std::endl << std::endl;
    mat = (MatrixXf(2, 2) << 0, 1, 2, 0).finished() * mat;    //此处使用了临时变量，然后使用逗号初始化，在此必须使用finish（）方法来获取实际的矩阵对象。
    std::cout << "after: " << endl << mat << std::endl;

    return 0;
}

/* output:
m0 =
 0.680375   0.59688 -0.329554
-0.211234  0.823295  0.536459
 0.566198 -0.604897 -0.444451
m1 =
2.4 2.4 2.4
2.4 2.4 2.4
2.4 2.4 2.4
m2 =
0 0
0 0
m3 =
1 1 1
1 1 1
1 1 1
m4 =
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
m5 =
1 2 3
4 5 6
7 8 9
before: 
1 1 1
1 1 1

after: 
1 1 1
2 2 2
*/