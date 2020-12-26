cmake_minimum_required(VERSION 3.15)

project(libmb)

set(CMAKE_PROJECT_VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
add_library(libmb error.cpp error.h int.h result.h tests/result_test.cpp)
