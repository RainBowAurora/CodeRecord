#include <Eigen/Dense>
#include <iostream>

int main(int argc, char *argv[])
{
    Eigen::ArrayXf v(6);
    v << 1, 2, 3, 4, 5, 6;
    std::cout << "v.head(3) =" << std::endl << v.head(3) << std::endl << std::endl;
    std::cout << "v.tail<3>() = " << std::endl << v.tail<3>() << std::endl << std::endl;
    v.segment(1,4) *= 2;
    std::cout << "after 'v.segment(1,4) *= 2', v =" << std::endl << v << std::endl;

    return 0;
}

/*output:
v.head(3) =
1
2
3

v.tail<3>() = 
4
5
6

after 'v.segment(1,4) *= 2', v =
 1
 4
 6
 8
10
 6
*/