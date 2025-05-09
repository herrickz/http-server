
#include "FileReader.h"
#include "Logger.h"

#include <iostream>
#include <fstream>
#include <vector>

FileReader::FileReader(const std::string &fileName) {

    std::fstream stream(fileName, std::fstream::in);

    if(stream.is_open()) {
        stream.seekg(0, std::fstream::end);

        const std::streampos fileSize = stream.tellg();

        stream.seekg(0, std::fstream::beg);

        std::vector<char> fileContentsArray;

        fileContentsArray.reserve((int)fileSize);

        stream.read(fileContentsArray.data(), fileSize);

        mFileContents = std::string(fileContentsArray.data());

        stream.close();
    }

}

std::string FileReader::GetString() {
    return mFileContents;
}