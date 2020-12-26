cmake_minimum_required(VERSION 3.15)

project(libmb)

include_directories(./include)

set(CMAKE_PROJECT_VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
add_library(libmb src/error.cpp include/mb/error.h include/mb/int.h include/mb/result.h tests/result_test.cpp)
