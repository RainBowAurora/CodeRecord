cmake_minimum_required(VERSION 3.4)                                                                                    
 
project(suffix_separation)

add_compile_options(-std=c++11)

if(NOT ENABLE_TRAVIS)
  find_package(GTest REQUIRED)
  message(STATUS "find_package ${ENABLE_TRAVIS}")
  include_directories(${GTEST_INCLUDE_DIRS})
endif()


add_executable(${PROJECT_NAME}_test suffix_separation_test.cpp )

target_link_libraries(${PROJECT_NAME}_test ${GTEST_BOTH_LIBRARIES})

enable_testing()
add_test(
  NAME google_test
  COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
  )
