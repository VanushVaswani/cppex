cmake_minimum_required(VERSION 3.4)
project(cppex CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(threads src/ex5.cpp)
add_subdirectory(include)
add_subdirectory(tests)
