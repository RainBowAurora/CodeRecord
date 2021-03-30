# Cmake 版本最低要求
cmake_minimum_required(VERSION 2.8.3) 

# 指定工程名字、版本号及支持的语言
project(thread_pool LANGUAGES CXX)  

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_executable(${PROJECT_NAME} thread_pool.cc main.cpp)