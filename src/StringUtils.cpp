
#include "StringUtils.h"
#include <iostream>

/**
 * @param line: Line to split
 * @param delimiter: Delimiter to use when splitting the line
 * @param times: Amount of times to split the line by the delimiter (Default 0 (split all instances))
 */
std::vector<std::string> splitLineOnDelimiter(const std::string &line, const char delim, uint32_t times) {

    std::vector<std::string> elements;

    uint32_t timesSplit = 0;

    size_t delimiterPosition = line.find(delim);
    size_t currentPosition = 0U;

    while(delimiterPosition != std::string::npos && (times == 0 || timesSplit < times)) {

        size_t characterCount = delimiterPosition - currentPosition;

        std::string subString = line.substr(currentPosition, characterCount);

        elements.push_back(subString);
        currentPosition = delimiterPosition + 1;
        timesSplit++;
        delimiterPosition = line.find(delim, currentPosition + 1);

    }

    if(currentPosition < line.size()) {
        size_t leftoverCharacterCount = line.size() - currentPosition;
        elements.push_back(line.substr(currentPosition, leftoverCharacterCount));
    }

    return elements;
}