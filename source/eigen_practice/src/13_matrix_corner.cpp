#include <eigen3/Eigen/Dense>
#include <iostream>


int main(int argc, char* argv[]) {
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16;
    std::cout << "m.leftCols(2) =" << std::endl << m.leftCols(2) << std::endl << std::endl;
    std::cout << "m.bottomRows<2>() =" << std::endl << m.bottomRows<2>() << std::endl << std::endl;
    m.topLeftCorner(1, 3) = m.bottomRightCorner(3, 1).transpose();
    std::cout << "After assignment, m = " << std::endl << m << std::endl;

    return 0;
}

/*output:
m.leftCols(2) =
 1  2
 5  6
 9 10
13 14

m.bottomRows<2>() =
 9 10 11 12
13 14 15 16

After assignment, m = 
 8 12 16  4
 5  6  7  8
 9 10 11 12
13 14 15 16
*/