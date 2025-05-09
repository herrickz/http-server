
#include "gtest/gtest.h"

#include "FileReader.h"

TEST(FileReader, canReadFile) {

    FileReader fileReader("myfile.txt");

    const std::string fileContents = fileReader.GetString();

    const std::string firstThreeLetters = fileContents.substr(0, 3);

    EXPECT_EQ(firstThreeLetters, "abc");
}