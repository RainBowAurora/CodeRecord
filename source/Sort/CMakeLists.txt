#Cmake 版本最低要求   
cmake_minimum_required(VERSION 3.4) 

# 设置工程名字、版本、链接、项目说明
project(sort_algorithm VERSION 1.0  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")

find_package(GTest)

# 添加需要编译的源码(存放源码的路径和名字)
add_executable(${PROJECT_NAME}_all_test all_test.cpp) 
target_link_libraries(${PROJECT_NAME}_all_test ${GTEST_BOTH_LIBRARIES} pthread)

# enable_testing()
# add_test(
#   NAME google_test
#   COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
#   ) 
