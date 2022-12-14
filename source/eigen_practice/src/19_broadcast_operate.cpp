#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc, char *argv[])
{
    Eigen::MatrixXf m(2,4);
    Eigen::VectorXf v(2);

    m << 1, 23, 6, 9,
        3, 11, 7, 2;

    v << 2,
        3;

    //add v to each column of m
    m.colwise() += v;
    
    std::cout << "Broadcasting result: " << std::endl;
    std::cout << m << std::endl;

    Eigen::MatrixXf::Index index;
    // find nearest neighbour
    (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
    std::cout << "Nearest neighbour is column " << index << ":" << std::endl;
    std::cout << m.col(index) << std::endl;

    return 0;
}

/*output:
 3 25  8 11
 6 14 10  5
Nearest neighbour is column 0:
3
6
*/