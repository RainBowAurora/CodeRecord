#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>


int main(int argc, char *argv[])
{
    // 旋转矩阵直接用Matrix3d即可
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix.setIdentity();
    // 旋转向量 由旋转轴和旋转角度组成
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1));
    std::cout.precision(3);
    std::cout << "rotation vector: Angle is: " << rotation_vector.angle() * (180 / M_PI)
         << "  Axis is: " << rotation_vector.axis().transpose() << std::endl;

    std::cout << "rotation matrix =\n" << rotation_vector.matrix() << std::endl;
    rotation_matrix = rotation_vector.toRotationMatrix();

    // 下面v是待旋转的向量，或者认为空间中的一个刚体的位置
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_vector * v;
    std::cout << "(1,0,0) after rotation = " << v_rotated.transpose() << std::endl;
    v_rotated = rotation_matrix * v;
    std::cout << "(1,0,0) after rotation = " << v_rotated.transpose() << std::endl;

    // 欧拉角 按ZYX的顺序 由旋转矩阵直接转换成欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    std::cout << "yaw pitch roll = " << euler_angles.transpose() * (180 / M_PI) << std::endl;

    // 变换矩阵  4x4的
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate(rotation_vector);
    // T.rotate(rotation_matrix);    // 这样写也行，相当于由旋转矩阵构造变换矩阵
    // 设置平移向量
    T.pretranslate(Eigen::Vector3d(0, 0, 3));
    std::cout << "Transform matrix = \n" << T.matrix() << std::endl;

    // 用变换矩阵进行坐标变换
    Eigen::Vector3d v_transformed = T * v;
    std::cout << "v transformed = " << v_transformed.transpose() << std::endl;

    // 由旋转向量构造四元数
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    std::cout << "quaternion = \n" << q.coeffs() << std::endl;

    // 由旋转矩阵构造四元数
    q = Eigen::Quaterniond(rotation_matrix);
    std::cout << "quaternion = \n" << q.coeffs() << std::endl;
    v_rotated = q * v;
    std::cout << "(1,0,0) after rotation = " << v_rotated.transpose() << std::endl;

    return 0;
}


/*output:
rotation vector: Angle is: 45  Axis is: 0 0 1
rotation matrix =
 0.707 -0.707      0
 0.707  0.707      0
     0      0      1
(1,0,0) after rotation = 0.707 0.707     0
(1,0,0) after rotation = 0.707 0.707     0
yaw pitch roll = 45 -0  0
Transform matrix = 
 0.707 -0.707      0      0
 0.707  0.707      0      0
     0      0      1      3
     0      0      0      1
v transformed = 0.707 0.707     3
quaternion = 
    0
    0
0.383
0.924
quaternion = 
    0
    0
0.383
0.924
(1,0,0) after rotation = 0.707 0.707     0
*/