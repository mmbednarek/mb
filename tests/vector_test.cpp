#include <gtest/gtest.h>
#include <mb/vector2d.h>

TEST(vector2d, basic_vector) {
    mb::vector2d<int> vec;
    auto at_result = vec.at(0, 0);
    ASSERT_FALSE(at_result.ok());
}

TEST(vector2d, basic_vector2) {
    mb::vector2d<int> vec;
    vec.set(0, 0, 12);
    auto at_result = vec.at(0, 0);
    ASSERT_TRUE(at_result.ok());
    ASSERT_EQ(at_result.unwrap(), 12);
}

TEST(vector2d, basic_vector3) {
    mb::vector2d<int> vec;
    for (auto y = -16; y < 16; ++y) {
        for (auto x = -16; x < 16; ++x) {
            vec.set(x, y, x + y);
        }
    }
    for (auto y = -16; y < 16; ++y) {
        for (auto x = -16; x < 16; ++x) {
            auto at_result = vec.at(x, y);
            ASSERT_EQ(at_result.unwrap(), x + y);
        }
    }
}

TEST(vector2d, basic_vector_get) {
    mb::vector2d<int> vec;
    for (auto y = -16; y < 16; ++y) {
        for (auto x = -16; x < 16; ++x) {
            vec.set(x, y, x + y);
        }
    }
    for (auto y = -16; y < 16; ++y) {
        for (auto x = -16; x < 16; ++x) {
            ASSERT_EQ(vec.get(x, y), x + y);
        }
    }
}
