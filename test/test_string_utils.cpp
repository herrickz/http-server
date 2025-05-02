
#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(MyTest, StringUtilsHelloWorldSplit) {

    std::string line = "hello world";

    auto elements = splitLineOnDelimiter(line, ' ');

    EXPECT_EQ(elements[0], "hello");
    EXPECT_EQ(elements[1], "world");
}

TEST(MyTest, StringUtilsHelloWorldSplitOnce) {

    std::string line = "hello world lets go";

    auto elements = splitLineOnDelimiter(line, ' ', 1);

    EXPECT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0], "hello");
    EXPECT_EQ(elements[1], "world lets go");
}

TEST(MyTest, StringUtilsHelloWorldSplitTwice) {

    std::string line = "hello world lets go";

    auto elements = splitLineOnDelimiter(line, ' ', 2);

    EXPECT_EQ(elements.size(), 3);
    EXPECT_EQ(elements[0], "hello");
    EXPECT_EQ(elements[1], "world");
    EXPECT_EQ(elements[2], "lets go");
}

TEST(MyTest, BasicAssertions) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
