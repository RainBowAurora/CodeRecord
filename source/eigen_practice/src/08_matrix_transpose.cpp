#include <iostream>
#include <eigen3/Eigen/Dense>

int main(int argc, char *argv[])
{
    Eigen::MatrixXcf a = Eigen::MatrixXcf::Random(2, 2);
    std::cout << "Here is the matrix a\n" << a << std::endl;
    std::cout << "Here is the matrix a^T\n" << a.transpose() << std::endl;
    std::cout << "Here is the conjugate of a\n" << a.conjugate() << std::endl;
    std::cout << "Here is the matrix a^*\n" << a.adjoint() << std::endl;

    Eigen::Matrix2i b;
    b << 1,2,
        3,4;

    std::cout << "Here is the matrix a:\n" << a << std::endl;
    //    a = a.transpose(); // !!! do NOT do this !!!       不要这样写代码，无法运行

    a.transposeInPlace();
    std::cout << "Here is the  transpose matrix a:\n" << a << std::endl;

    return 0;
}

/*output:
Here is the matrix a
(-0.211234,0.680375) (-0.604897,0.823295)
  (0.59688,0.566198) (0.536459,-0.329554)
Here is the matrix a^T
(-0.211234,0.680375)   (0.59688,0.566198)
(-0.604897,0.823295) (0.536459,-0.329554)
Here is the conjugate of a
(-0.211234,-0.680375) (-0.604897,-0.823295)
  (0.59688,-0.566198)   (0.536459,0.329554)
Here is the matrix a^*
(-0.211234,-0.680375)   (0.59688,-0.566198)
(-0.604897,-0.823295)   (0.536459,0.329554)
Here is the matrix a:
(-0.211234,0.680375) (-0.604897,0.823295)
  (0.59688,0.566198) (0.536459,-0.329554)
Here is the  transpose matrix a:
(-0.211234,0.680375)   (0.59688,0.566198)
(-0.604897,0.823295) (0.536459,-0.329554)
*/