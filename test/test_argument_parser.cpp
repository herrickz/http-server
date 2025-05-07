
#include <gtest/gtest.h>

#include "ArgumentParser.h"


TEST(ArgumentParser, oneIntegerArgumentShortName) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "http-server", "-p", "2000" };

    int arrayElements = sizeof(array) / sizeof(char*);

    char **argv = array;

    argumentParser.ParseArguments(arrayElements, argv);

    EXPECT_EQ(argumentParser.GetValue<int>("p"), 2000);
    EXPECT_EQ(argumentParser.GetValue<int>("port"), 2000);
}

TEST(ArgumentParser, oneIntegerArgumentLongName) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "http-server", "--port", "3000" };

    int arrayElements = sizeof(array) / sizeof(char*);

    char **argv = array;

    argumentParser.ParseArguments(arrayElements, argv);

    EXPECT_EQ(argumentParser.GetValue<int>("p"), 3000);
    EXPECT_EQ(argumentParser.GetValue<int>("port"), 3000);
}

TEST(ArgumentParser, oneStringArgumentShortName) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "path");

    char *array[] = { "http-server", "-p", "/usr/bin" };

    int arrayElements = sizeof(array) / sizeof(char*);

    char **argv = array;

    argumentParser.ParseArguments(arrayElements, argv);

    EXPECT_EQ(argumentParser.GetValue<std::string>("p"), "/usr/bin");
    EXPECT_EQ(argumentParser.GetValue<std::string>("path"), "/usr/bin");
}

TEST(ArgumentParser, oneIntegerArgumentShortNameAndOneStringLongNameArgument) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");
    argumentParser.AddArgument("n", "name");

    char *array[] = { "http-server", "-p", "4", "--name", "hello" };

    int arrayElements = sizeof(array) / sizeof(char*);

    char **argv = array;

    argumentParser.ParseArguments(arrayElements, argv);

    EXPECT_EQ(argumentParser.GetValue<std::string>("n"), "hello");
    EXPECT_EQ(argumentParser.GetValue<std::string>("name"), "hello");

    EXPECT_EQ(argumentParser.GetValue<int>("p"), 4);
    EXPECT_EQ(argumentParser.GetValue<int>("port"), 4);
}

TEST(ArgumentParser, unevenAmountOfArgumentsThrowsException) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "http-server", "-p", "asd", "44444" };

    int arrayElements = sizeof(array) / sizeof(char*);

    char **argv = array;

    try {

        argumentParser.ParseArguments(arrayElements, argv);

        FAIL() << "Was able to parse uneven amount of arguments";

    } catch(std::exception &exception) {
        EXPECT_TRUE(true);
    }

}

TEST(ArgumentParser, getIntegerWithNoArgumentsReturnsDefault0) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");

    char *array[] = { "http-server" };

    int arrayElements = sizeof(array) / sizeof(char*);

    char **argv = array;

    argumentParser.ParseArguments(arrayElements, argv);

    EXPECT_EQ(argumentParser.GetValue<int>("p"), 0);

}

