cmake_minimum_required(VERSION 3.4)

project(test_poco)

add_library(factory SHARED factory.cpp)
add_library(derived_plugin SHARED derived.cpp)
target_link_libraries(derived_plugin factory)


find_package(Poco REQUIRED COMPONENTS Foundation)
add_executable(${PROJECT_NAME}_node main.cpp)
target_link_libraries(${PROJECT_NAME}_node Poco::Foundation factory)
