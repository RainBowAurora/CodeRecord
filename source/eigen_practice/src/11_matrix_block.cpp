#include <eigen3/Eigen/Dense>
#include <iostream>

int main(int argc, char *argv[]) {
    Eigen::MatrixXf m(4, 4);
    // 初始化m矩阵
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m(i, j) = j + 1 + i * 4;
        }
    }
    std::cout << "m: " << std::endl << m << std::endl;
    std::cout << "Block in the middle" << std::endl;
    std::cout << m.block<2, 2>(1, 1) << std::endl << std::endl;      // m.block<i,j> (a,b) 表示从第(a+1)行(b+1)列开始,截图i行,j列
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Block of size " << i << "x" << i << std::endl;
        std::cout << m.block(0, 0, i, i) << std::endl << std::endl;  //m.block(a,b,i,j) 表示从第(a+1)行(b+1)列开始,截图i行,j列
    }

    Eigen::Array22f n;
    n << 1, 2,
            3, 4;
    Eigen::Array44f a = Eigen::Array44f::Constant(0.6);
    std::cout << "Here is the array a:" << std::endl << a << std::endl << std::endl;
    a.block<2, 2>(1, 1) = n;
    std::cout << "Here is now a with m copied into its central 2x2 block:" << std::endl << a << std::endl << std::endl;
    a.block(0, 0, 2, 3) = a.block(2, 1, 2, 3);
    std::cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:" << std::endl << a << std::endl << std::endl;


    return 0;
}

/*output:
m: 
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
Block in the middle
 6  7
10 11

Block of size 1x1
1

Block of size 2x2
1 2
5 6

Block of size 3x3
 1  2  3
 5  6  7
 9 10 11

Here is the array a:
0.6 0.6 0.6 0.6
0.6 0.6 0.6 0.6
0.6 0.6 0.6 0.6
0.6 0.6 0.6 0.6

Here is now a with m copied into its central 2x2 block:
0.6 0.6 0.6 0.6
0.6   1   2 0.6
0.6   3   4 0.6
0.6 0.6 0.6 0.6

Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:
  3   4 0.6 0.6
0.6 0.6 0.6 0.6
0.6   3   4 0.6
0.6 0.6 0.6 0.6
*/
