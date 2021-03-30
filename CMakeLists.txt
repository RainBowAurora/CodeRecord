# Cmake 版本最低要求
cmake_minimum_required(VERSION 2.8.3)
if( POLICY CMP0048 )
  cmake_policy( SET CMP0048 NEW ) # CMake 3.0
endif()

project(all)

option (ENABLE_TRAVIS
"Use ENABLE_TRAVIS" OFF) 

if(ENABLE_TRAVIS)
  include(GoogleTest.cmake)
  set(GTEST_BOTH_LIBRARIES gtest_main)
endif()

include(SubDirName.cmake)



