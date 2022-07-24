cmake_minimum_required(VERSION 3.9)
project(libmb)

set(CMAKE_CXX_STANDARD 20)

option(LIMB_BUILD_TEST "Build unit tests" OFF)

if(LIMB_BUILD_TEST)
    add_subdirectory(tests)
endif(LIMB_BUILD_TEST)

add_library(libmb src/error.cpp include/mb/error.h include/mb/int.h include/mb/result.h include/mb/view.h include/mb/core.h include/mb/enum.h src/core.cpp include/mb/compile_time.h)
target_include_directories(libmb PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)