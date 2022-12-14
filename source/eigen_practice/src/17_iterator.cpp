#include <iostream>
#include <Eigen/Dense>

int main(int argc, char *argv[])
{
    Eigen::MatrixXf m(2,2);

    m << 1, 2,
        3, 4;
    //get location of maximum
    Eigen::MatrixXf::Index maxRow, maxCol;
    float max = m.maxCoeff(&maxRow, &maxCol);
    //get location of minimum
    Eigen::MatrixXf::Index minRow, minCol;
    float min = m.minCoeff(&minRow, &minCol);
    std::cout << "Max: " << max <<  ", at: " <<
        maxRow << "," << maxCol << std::endl;
    std::cout << "Min: " << min << ", at: " <<
        minRow << "," << minCol << std::endl;

    return 0;
}

/*output:
Max: 4, at: 1,1
Min: 1, at: 0,0
*/