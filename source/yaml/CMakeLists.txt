cmake_minimum_required(VERSION 3.4)

project(yaml)

add_compile_options(-std=c++11)

find_package(yaml-cpp 0.6.3)

add_executable(${PROJECT_NAME}_node yaml_cpp_test.cpp)
target_link_libraries(${PROJECT_NAME}_node yaml-cpp)
