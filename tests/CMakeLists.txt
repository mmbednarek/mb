cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(gtest)

add_executable(mb_test result_test.cpp)
target_link_libraries(mb_test LINK_PUBLIC libmb gtest gtest_main)