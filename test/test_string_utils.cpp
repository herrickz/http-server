
#include <gtest/gtest.h>
#include "StringUtils.h"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std::chrono_literals;

TEST(StringUtil, HelloWorldSplit) {

    std::string line = "hello world";

    auto elements = splitLineOnDelimiter(line, ' ');

    EXPECT_EQ(elements[0], "hello");
    EXPECT_EQ(elements[1], "world");
}

TEST(StringUtil, HelloWorldSplitOnce) {

    std::string line = "hello world lets go";

    auto elements = splitLineOnDelimiter(line, ' ', 1);

    EXPECT_EQ(elements.size(), 2);
    EXPECT_EQ(elements[0], "hello");
    EXPECT_EQ(elements[1], "world lets go");
}

TEST(StringUtil, HelloWorldSplitTwice) {

    std::string line = "hello world lets go";

    auto elements = splitLineOnDelimiter(line, ' ', 2);

    EXPECT_EQ(elements.size(), 3);
    EXPECT_EQ(elements[0], "hello");
    EXPECT_EQ(elements[1], "world");
    EXPECT_EQ(elements[2], "lets go");
}

TEST(StringUtil, splitStringOnDelimiterPerformance) {

    const int32_t TESTS_TO_PERFORM = 10000;
    std::vector<long> splitStringDurations;

    for(int i = 0; i < TESTS_TO_PERFORM; i++) {

        auto begin = std::chrono::high_resolution_clock::now();

        std::string line = "hello world lets go";

        auto elements = splitLineOnDelimiter(line, ' ');

        auto end = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<long, std::nano> difference = end - begin;

        splitStringDurations.push_back(difference.count());
    }

    auto sumLambda = [](long a, long b) { return a + b; };

    auto total = std::accumulate(
        splitStringDurations.begin(),
        splitStringDurations.end(),
        0,
        sumLambda
    );

    std::cout << "Average: " << total / splitStringDurations.size() << " nanoseconds" <<  std::endl;
}

