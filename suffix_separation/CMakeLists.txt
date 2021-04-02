cmake_minimum_required(VERSION 3.4)                                                                                    
 
project(suffix_separation)

add_compile_options(-std=c++11)

find_package(GTest)

add_executable(${PROJECT_NAME}_test suffix_separation_test.cpp )

target_link_libraries(${PROJECT_NAME}_test ${GTEST_BOTH_LIBRARIES})

enable_testing()
add_test(
  NAME google_test
  COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
  )
