
#include <gtest/gtest.h>

#include "ArgumentParser.h"


TEST(ArgumentParser, oneIntegerArgumentShortName) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "-p", "2000" };

    char **argv = array;

    argumentParser.ParseArguments(2, argv);

    EXPECT_EQ(argumentParser.getValue<int>("p"), 2000);
    EXPECT_EQ(argumentParser.getValue<int>("port"), 2000);
}

TEST(ArgumentParser, oneIntegerArgumentLongName) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "--port", "3000" };

    char **argv = array;

    argumentParser.ParseArguments(2, argv);

    EXPECT_EQ(argumentParser.getValue<int>("p"), 3000);
    EXPECT_EQ(argumentParser.getValue<int>("port"), 3000);
}

