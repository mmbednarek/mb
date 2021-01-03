#include <mb/view.h>
#include <gtest/gtest.h>

TEST(view, from_array) {
    std::array<mb::i32, 3> l_arr{ 3, 4, 5 };
    mb::view<mb::i32> l_view(l_arr);

    ASSERT_EQ(l_view.size(), 3);
    ASSERT_EQ(l_view.data(), l_arr.data());

    ASSERT_EQ(l_view[0], 3);
    ASSERT_EQ(l_view[1], 4);
    ASSERT_EQ(l_view[2], 5);

    std::for_each(l_view.begin(), l_view.end(), [expected = 3](const mb::i32 value) mutable {
        ASSERT_EQ(value, expected);
        ++expected;
    });
}

TEST(view, from_vector) {
    std::vector<mb::i32> l_vec{ 3, 4, 5 };
    mb::view<mb::i32> l_view(l_vec);

    ASSERT_EQ(l_view.size(), l_vec.size());
    ASSERT_EQ(l_view.data(), l_vec.data());

    ASSERT_EQ(l_view[0], 3);
    ASSERT_EQ(l_view[1], 4);
    ASSERT_EQ(l_view[2], 5);

    std::for_each(l_view.begin(), l_view.end(), [expected = 3](const mb::i32 value) mutable {
      ASSERT_EQ(value, expected);
      ++expected;
    });
}
