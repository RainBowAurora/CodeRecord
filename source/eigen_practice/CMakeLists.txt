#Cmake 版本最低要求   
cmake_minimum_required(VERSION 3.4) 

# 设置工程名字、版本、链接、项目说明
project(eigen_practice VERSION 1.0  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# 添加需要编译的源码(存放源码的路径和名字)
add_executable(01_sample_program src/01_sample_program.cpp) 
add_executable(02_matrix_and_vectors src/02_matrix_and_vectors.cpp) 
add_executable(03_eigen_initialize src/03_eigen_initialize.cpp) 
add_executable(04_resize_function src/04_resize_function.cpp) 
add_executable(05_array_operate src/05_array_operate.cpp) 
add_executable(06_array_function src/06_array_function.cpp) 
add_executable(07_array2matrix src/07_array2matrix.cpp) 
add_executable(08_matrix_transpose src/08_matrix_transpose.cpp) 
add_executable(09_dot_and_cross src/09_dot_and_cross.cpp) 
add_executable(10_matrix_function src/10_matrix_function.cpp) 
add_executable(11_matrix_block src/11_matrix_block.cpp) 
add_executable(12_col_and_row src/12_col_and_row.cpp) 
add_executable(13_matrix_corner src/13_matrix_corner.cpp) 
add_executable(14_vector_block src/14_vector_block.cpp) 
add_executable(15_squared_norm src/15_squared_norm.cpp) 
add_executable(16_statute_boolean src/16_statute_boolean.cpp) 
add_executable(17_iterator src/17_iterator.cpp) 
add_executable(18_partial_regulations src/18_partial_regulations.cpp) 
add_executable(19_broadcast_operate src/19_broadcast_operate.cpp) 
add_executable(20_geometry src/20_geometry.cpp) 
