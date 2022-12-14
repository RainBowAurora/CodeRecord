#include <iostream>
#include <Eigen/Dense>

int main(int argc, char *argv[])
{
    Eigen::MatrixXf mat1(2,4);
    mat1 << 1, 2, 6, 9,
            3, 1, 7, 2;

    std::cout << "Column's maximum: " << std::endl
    << mat1.colwise().maxCoeff() << std::endl;


    Eigen::MatrixXf mat2(2,4);
    mat2 << 1, 2, 6, 9,
            3, 1, 7, 2;

    std::cout << "Row's maximum: " << std::endl
    << mat2.rowwise().maxCoeff() << std::endl;

    Eigen::MatrixXf mat3(2,4);
    mat3 << 1, 2, 6, 9,
            3, 1, 7, 2;

    Eigen::MatrixXf::Index   maxIndex;
    float maxNorm = mat3.colwise().sum().maxCoeff(&maxIndex);

    std::cout << "Maximum sum at position " << maxIndex << std::endl;
    std::cout << "The corresponding vector is: " << std::endl;
    std::cout << mat3.col( maxIndex ) << std::endl;
    std::cout << "And its sum is is: " << maxNorm << std::endl;

   return 0;
}

/*output:
Column's maximum: 
3 2 7 9

Row's maximum: 
9
7

Maximum sum at position 2
The corresponding vector is: 
6
7
And its sum is is: 13

*/