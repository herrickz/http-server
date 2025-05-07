
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

TEST(ArgumentParser, oneStringArgumentShortName) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "path");

    char *array[] = { "-p", "/usr/bin" };

    char **argv = array;

    argumentParser.ParseArguments(2, argv);

    EXPECT_EQ(argumentParser.getValue<std::string>("p"), "/usr/bin");
    EXPECT_EQ(argumentParser.getValue<std::string>("path"), "/usr/bin");
}

TEST(ArgumentParser, oneIntegerArgumentShortNameAndOneStringLongNameArgument) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");
    argumentParser.AddArgument("n", "name");

    char *array[] = { "-p", "4", "--name", "hello" };

    char **argv = array;

    argumentParser.ParseArguments(4, argv);

    EXPECT_EQ(argumentParser.getValue<std::string>("n"), "hello");
    EXPECT_EQ(argumentParser.getValue<std::string>("name"), "hello");

    EXPECT_EQ(argumentParser.getValue<int>("p"), 4);
    EXPECT_EQ(argumentParser.getValue<int>("port"), 4);
}

TEST(ArgumentParser, unevenAmountOfArgumentsThrowsException) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "-p", "asd", "44444" };

    char **argv = array;

    try {

        argumentParser.ParseArguments(3, argv);
        FAIL() << "Was able to parse uneven amount of arguments";

    } catch(std::exception &exception) {
        std::cout << exception.what() << std::endl;
        EXPECT_TRUE(true);
    }

}

