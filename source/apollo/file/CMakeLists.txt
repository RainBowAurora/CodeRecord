cmake_minimum_required(VERSION 3.4)

project(cyber_file)

add_compile_options(-std=c++11)

# find_package(yaml-cpp 0.6.3)

add_library(file SHARED cyber_file.cpp)
# target_link_libraries(file yaml-cpp)

find_package(GTest)
add_executable(${PROJECT_NAME}_test cyber_file_test.cpp)
target_link_libraries(${PROJECT_NAME}_test file ${GTEST_BOTH_LIBRARIES} pthread)
