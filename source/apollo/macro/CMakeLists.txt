cmake_minimum_required(VERSION 3.4)

project(macro)

add_compile_options(-std=c++11)

find_package(GTest)
add_executable(${PROJECT_NAME}_test macro_test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${GTEST_BOTH_LIBRARIES} pthread)
