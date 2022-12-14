#include <Eigen/Dense>
#include <iostream>

int main(int argc, char* argv[]) {
    Eigen::MatrixXf m(4, 4);
    // 数组初始化
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m(i, j) = j + 1 + i * 4;
        }
    }
    std::cout << "Here is the matrix m:" << std::endl << m << std::endl;
    std::cout << "2nd Row: " << m.row(1) << std::endl;
    m.col(2) += 3 * m.col(0);
    std::cout << "After adding 3 times the first column into the third column, the matrix m is:\n";
    std::cout << m << std::endl;
    return 0;
}

/*output:
Here is the matrix m:
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
2nd Row: 5 6 7 8
After adding 3 times the first column into the third column, the matrix m is:
 1  2  6  4
 5  6 22  8
 9 10 38 12
13 14 54 16
*/
