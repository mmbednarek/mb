cmake_minimum_required(VERSION 3.15)
project(libmb)

set(CMAKE_CXX_STANDARD 17)

add_library(libmb src/error.cpp include/mb/error.h include/mb/int.h include/mb/result.h)
target_include_directories(libmb PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
