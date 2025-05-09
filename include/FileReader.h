#pragma once

#include <string>

class FileReader {

public:

    FileReader(const std::string &fileName);

    std::string GetString();

private:

    std::string mFileContents;

};
