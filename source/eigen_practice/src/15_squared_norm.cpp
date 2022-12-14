#include <eigen3/Eigen/Dense>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    Eigen::VectorXf v(2);
    Eigen::MatrixXf m(2, 2), n(2, 2);

    v << -1, 2;

    m << 1, -2, -3, 4;
    std::cout << "v.squaredNorm() = " << v.squaredNorm() << std::endl;
    std::cout << "v.norm() = " << v.norm() << std::endl;
    std::cout << "v.lpNorm<1>() = " << v.lpNorm<1>() << std::endl;
    std::cout << "v.lpNorm<Infinity>() = " << v.lpNorm<Eigen::Infinity>() << std::endl;
    std::cout << std::endl;
    std::cout << "m.squaredNorm() = " << m.squaredNorm() << std::endl;
    std::cout << "m.norm() = " << m.norm() << std::endl;
    std::cout << "m.lpNorm<1>() = " << m.lpNorm<1>() << std::endl;
    std::cout << "m.lpNorm<Infinity>() = " << m.lpNorm<Eigen::Infinity>() << std::endl;



  Eigen::MatrixXf w(2,2);
  w << 1,-2,
       -3,4;
  std::cout << "1-norm(m)     = " << w.cwiseAbs().colwise().sum().maxCoeff()
       << " == "             << w.colwise().lpNorm<1>().maxCoeff() << std::endl;
  std::cout << "infty-norm(m) = " << w.cwiseAbs().rowwise().sum().maxCoeff()
       << " == "             << w.rowwise().lpNorm<1>().maxCoeff() << std::endl;

    return 0;
}

/*output:
v.squaredNorm() = 5
v.norm() = 2.23607
v.lpNorm<1>() = 3
v.lpNorm<Infinity>() = 2

m.squaredNorm() = 30
m.norm() = 5.47723
m.lpNorm<1>() = 10
m.lpNorm<Infinity>() = 4
1-norm(m)     = 6 == 6
infty-norm(m) = 7 == 7
*/