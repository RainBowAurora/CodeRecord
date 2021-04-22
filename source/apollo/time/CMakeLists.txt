# Cmake 版本最低要求
cmake_minimum_required(VERSION 2.8.3) 

# 指定工程名字、版本号及支持的语言
project(chrono_time LANGUAGES CXX)  

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

add_library(chrono_time SHARED chrono_time.cpp chrono_duration.cpp)

add_library(chrono_duration SHARED chrono_duration.cpp)

add_library(chrono_rate SHARED chrono_rate.cpp)
target_link_libraries(chrono_rate chrono_duration chrono_time)

find_package(GTest)
add_executable(${PROJECT_NAME}_test all_time_test.cpp)

target_link_libraries(${PROJECT_NAME}_test chrono_duration chrono_time ${GTEST_BOTH_LIBRARIES} pthread)
