#include <gtest/gtest.h>
#include <mb/enum.h>

enum class DirectionValues {
    Forward,
    Backward
};

using Direction_Base = mb::enum_wrapper<DirectionValues, "forward", "backward">;

class Direction final : public Direction_Base {
public:
    MB_ENUM_TRAITS(Direction)

    MB_ENUM_FIELD(Forward);
    MB_ENUM_FIELD(Backward);

    [[nodiscard]] constexpr Direction opposite() const {
        if (index() == Direction::Forward) {
            return Direction::Backward;
        }
        return Direction::Forward;
    }
};

TEST(EnumTest, StringEqual) {
    ASSERT_TRUE(mb::const_string{"hello"} == "hello");
    ASSERT_FALSE(mb::const_string{"hello"} == "helfo");
}

TEST(EnumTest, FindIndex_0) {
    auto index = mb::find_index<int, "foo", "bar">("foo");
    ASSERT_EQ(index, 0);
}

TEST(EnumTest, FindIndex_1) {
    auto index = mb::find_index<int, "foo", "bar">("bar");
    ASSERT_EQ(index, 1);
}

TEST(EnumTest, FindIndex_2) {
    auto index = mb::find_index<int, "foo", "bar", "hoo", "mar">("hoo");
    ASSERT_EQ(index, 2);
}

TEST(EnumTest, BasicCase) {
    switch (Direction::from_string("backward")) {
    case Direction::Forward:
        ASSERT_TRUE(false);
        break;
    case Direction::Backward:
        ASSERT_TRUE(true);
        break;
    default:
        ASSERT_TRUE(false);
    }
}

TEST(EnumTest, MethodTest) {
    auto cb = [](Direction dir) {
      ASSERT_EQ(dir.opposite(), Direction::Backward);
    };

    cb(Direction::Forward);
}

TEST(EnumTest, ToStringTest) {
    using namespace std::string_view_literals;
    std::string s{"forward"};
    ASSERT_EQ(MB_E(Direction, Forward).to_string(), "forward"sv);
}

TEST(EnumTest, ValuesTest) {
    using namespace std::string_view_literals;
    ASSERT_EQ(Direction::Values[0], DirectionValues::Forward);
    ASSERT_EQ(Direction::Values[1], DirectionValues::Backward);
}
