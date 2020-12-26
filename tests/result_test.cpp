#include "mb/int.h"
#include "mb/result.h"
#include <gtest/gtest.h>

using mb::i32;

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

mb::result<mb::f32> test_pass(i32 a, i32 b) {
    return 2.5 + mb_pass(divide(a, b));
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
    ASSERT_EQ(*res8.unwrap(), 16);
}