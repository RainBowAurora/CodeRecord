# Cmake 版本最低要求
cmake_minimum_required(VERSION 2.8.3) 

# 指定工程名字、版本号及支持的语言
project(thread_pool LANGUAGES CXX)  

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package(GTest)

add_executable(${PROJECT_NAME}_test thread_pool_test.cpp)

target_link_libraries(${PROJECT_NAME}_test ${GTEST_BOTH_LIBRARIES} pthread)

enable_testing()
add_test(
  NAME google_test
  COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
  )