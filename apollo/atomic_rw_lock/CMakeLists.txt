#Cmake 版本最低要求                                                                                                                                                                                                                          
cmake_minimum_required(VERSION 3.4) 

# 设置工程名字、版本、链接、项目说明
project(atomic_rw_lock VERSION 1.0  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(GTest REQUIRED)

# 添加需要编译的源码(存放源码的路径和名字)
add_executable(${PROJECT_NAME}_test atomic_rw_lock_test.cpp) 
target_link_libraries(${PROJECT_NAME}_test ${GTEST_BOTH_LIBRARIES})

enable_testing()
add_test(
  NAME google_test
  COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
  ) 