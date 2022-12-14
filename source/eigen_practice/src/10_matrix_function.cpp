#include <iostream>
#include <Eigen/Dense>

int main()
{
    Eigen::Matrix2d mat;
    mat << 1, 2,
            3, 4;
    std::cout << "Here is mat.sum():       " << mat.sum()       << std::endl;
    std::cout << "Here is mat.prod():      " << mat.prod()      << std::endl;
    std::cout << "Here is mat.mean():      " << mat.mean()      << std::endl;
    std::cout << "Here is mat.minCoeff():  " << mat.minCoeff()  << std::endl;
    std::cout << "Here is mat.maxCoeff():  " << mat.maxCoeff()  << std::endl;
    std::cout << "Here is mat.trace():     " << mat.trace()     << std::endl;


    Eigen::Matrix3f m = Eigen::Matrix3f::Random();
    std::ptrdiff_t i, j;
    float minOfM = m.minCoeff(&i,&j);
    std::cout << "Here is the matrix m:\n" << m << std::endl;
    std::cout << "Its minimum coefficient (" << minOfM 
        << ") is at position (" << i << "," << j << ")\n\n";
    Eigen::RowVector4i v = Eigen::RowVector4i::Random();
    int maxOfV = v.maxCoeff(&i);
    std::cout << "Here is the vector v: " << v << std::endl;
    std::cout << "Its maximum coefficient (" << maxOfV 
        << ") is at position " << i << std::endl;


    return 0;
}

/*output:
Here is mat.sum():       10
Here is mat.prod():      24
Here is mat.mean():      2.5
Here is mat.minCoeff():  1
Here is mat.maxCoeff():  4
Here is mat.trace():     5

Here is the matrix m:
 0.680375   0.59688 -0.329554
-0.211234  0.823295  0.536459
 0.566198 -0.604897 -0.444451
Its minimum coefficient (-0.604897) is at position (2,1)

Here is the vector v:  115899597  -48539462  276748203 -290373134
Its maximum coefficient (276748203) is at position 2

*/