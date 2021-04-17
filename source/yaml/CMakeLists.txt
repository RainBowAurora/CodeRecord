cmake_minimum_required(VERSION 3.4)

project(yaml_node)

add_compile_options(-std=c++11)

find_package(GTest)

find_package(yaml-cpp 0.6.3)

if(NOT yaml-cpp_FOUND)
FetchContent_Declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.6.3
)
FetchContent_GetProperties(googletest)
endif()

add_executable(${PROJECT_NAME}_test yaml_cpp_test.cpp)
target_link_libraries(${PROJECT_NAME}_test yaml-cpp)
