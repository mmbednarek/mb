#include "mb/int.h"
#include "mb/result.h"
#include <gtest/gtest.h>

using mb::i32, mb::f32;

// static size
mb::result<i32> divide(i32 a, i32 b) {
    if (b == 0)
        return mb::error("cannot divide by zero");
    return a / b;
}

// void result
mb::result<mb::empty> test_empty(i32 a) {
    if (a > 10)
        return mb::error("some error");
    return mb::ok;
}

mb::result<f32> test_pass(i32 a, i32 b) {
    return 2.5 + MB_TRY(divide(a, b));
}

struct test {
    i32 v;
};

mb::result<i32 &> test_ref(test &t) {
    return t.v;
}

mb::result<std::unique_ptr<i32>> test_ptr() {
    return std::make_unique<i32>(16);
}

TEST(result, ok) {
    auto res = divide(10, 5);
    ASSERT_TRUE(res.ok());
    ASSERT_EQ(res.unwrap(), 2);

    auto res2 = divide(10, 0);
    ASSERT_FALSE(res2.ok());
    ASSERT_EQ(res2.unwrap(111), 111);

    auto res3 = test_empty(2);
    ASSERT_TRUE(res3.ok());

    auto res4 = test_empty(30);
    ASSERT_FALSE(res4.ok());
    ASSERT_EQ(res4.err()->msg(), "some error");

    auto res5 = test_pass(10, 5);
    ASSERT_TRUE(res5.ok());
    ASSERT_EQ(res5.unwrap(), 4.5);

    auto res6 = test_pass(10, 0);
    ASSERT_FALSE(res6.ok());

    test t{};
    t.v = 8;

    auto res7 = test_ref(t);
    t.v = 16;
    ASSERT_TRUE(res7.ok());
    ASSERT_EQ(res7.unwrap(), t.v);

    auto res8 = test_ptr();
    ASSERT_TRUE(res8.ok());
    auto res8value = res8.unwrap();
    ASSERT_EQ(*res8value, 16);
    auto res8ref = mb::result<std::unique_ptr<i32> &>(res8value);
    auto res8ref_copy = mb::result<std::unique_ptr<i32> &>(res8ref);
}

TEST(result, unpack) {
    std::vector<mb::result<i32>> values{
            4, 5, 6};

    std::vector<i32> expected_unpacked{
            4, 5, 6};

    auto unpacked = mb::unpack(values);
    ASSERT_TRUE(unpacked.ok());
    ASSERT_EQ(unpacked.unwrap(), expected_unpacked);
}

TEST(result, unpack_non_copiable) {
    std::vector<mb::result<std::unique_ptr<i32>>> values;
    values.reserve(3);
    values.emplace_back(std::make_unique<i32>(4));
    values.emplace_back(std::make_unique<i32>(5));
    values.emplace_back(std::make_unique<i32>(6));

    auto unpacked = mb::unpack(values);
    ASSERT_TRUE(unpacked.ok());
    auto unpacked_value = unpacked.unwrap();
    ASSERT_EQ(unpacked_value.size(), 3);
    ASSERT_EQ(*unpacked_value.at(0), 4);
    ASSERT_EQ(*unpacked_value.at(1), 5);
    ASSERT_EQ(*unpacked_value.at(2), 6);
}

TEST(result, unpack_error) {
    std::vector<mb::result<i32>> values{
            4, 5, mb::error("some error")};

    auto unpacked = mb::unpack(values);
    ASSERT_FALSE(unpacked.ok());
    ASSERT_EQ(unpacked.err()->msg(), "some error");
}

TEST(result, unpack_non_copiable_error) {
    std::vector<mb::result<std::unique_ptr<i32>>> values;
    values.reserve(3);
    values.emplace_back(std::make_unique<i32>(4));
    values.emplace_back(std::make_unique<i32>(5));
    values.emplace_back(mb::error("some error"));

    auto unpacked = mb::unpack(values);
    ASSERT_FALSE(unpacked.ok());
    ASSERT_EQ(unpacked.err()->msg(), "some error");
}
