find_package(GTest REQUIRED)

add_executable(mb_test result_test.cpp view_test.cpp vector_test.cpp enum_test.cpp)
target_link_libraries(mb_test LINK_PUBLIC libmb gtest gtest_main)