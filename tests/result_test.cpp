#include "mb/int.h"
#include "mb/result.h"
#include <gtest/gtest.h>


struct no_copy_or_move {
    int value{};

    explicit no_copy_or_move(int value) : value(value) {}
    no_copy_or_move(no_copy_or_move &other) = delete;
    no_copy_or_move(no_copy_or_move &&other) noexcept = delete;
    no_copy_or_move &operator=(no_copy_or_move &other) = delete;
    no_copy_or_move &operator=(no_copy_or_move &&other) noexcept = delete;
};

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
    auto &res8value = res8.get();
    ASSERT_EQ(*res8value, 16);
    auto res8ref = mb::result<std::unique_ptr<i32> &>(res8value);
    auto res8ref_copy = mb::result<std::unique_ptr<i32> &>(res8ref);
}

TEST(result, try_non_copyable) {
    no_copy_or_move value{5};

    auto foo = [&value](bool create) -> mb::result<no_copy_or_move &> {
        if (!create) {
            return mb::error("err");
        }
        return value;
    };

    auto bar = [&foo]() -> mb::result<int> {
        auto &val = MB_TRY(foo(true));
        return std::move(val.value);
    };

    auto bar_res = bar();

    ASSERT_TRUE(bar_res.ok());
    ASSERT_EQ(bar_res.unwrap(0), 5);
    ASSERT_EQ(value.value, 5);
}

TEST(result, unpack) {
    std::vector<mb::result<i32>> values{
            4, 5, 6};

    std::vector<i32> expected_unpacked{
            4, 5, 6};

    std::vector<i32> unpacked(3);

    auto err = mb::unpack(values.begin(), values.end(),  unpacked.begin());
    ASSERT_TRUE(err == nullptr);
    ASSERT_EQ(unpacked, expected_unpacked);
}

TEST(result, unpack_error) {
    std::vector<mb::result<i32>> values{
            4, 5, mb::error("some error")};

    std::vector<i32> unpacked(values.size());
    auto err = mb::unpack(values.begin(), values.end(), unpacked.begin());
    ASSERT_FALSE(err == nullptr);
    ASSERT_EQ(err->msg(), "some error");
}