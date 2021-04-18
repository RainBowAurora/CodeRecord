cmake_minimum_required(VERSION 3.4)

project(gtest_assert)

find_package(GTest)

add_executable(${PROJECT_NAME}_test gtest_all.cpp)
target_link_libraries(${PROJECT_NAME}_test ${GTEST_BOTH_LIBRARIES} ${GMOCK_LIBRARIES} pthread)

enable_testing()
add_test(
  NAME google_test
  COMMAND $<TARGET_FILE:${PROJECT_NAME}_test>
  ) 



