
#include "StringUtils.h"

/**
 * @param line: Line to split
 * @param delimiter: Delimiter to use when splitting the line
 * @param times: Amount of times to split the line by the delimiter (Default 0 (split all instances))
 */
std::vector<std::string> splitLineOnDelimiter(const std::string &line, const char delim, int times) {

    std::vector<std::string> elements;
    std::string currentElement = "";

    uint32_t timesSplit = 0;

    for(int i = 0; i < line.size(); i++) {

        bool shouldSplit = (times == 0 || timesSplit < times);

        if(line[i] == delim && currentElement != "" && shouldSplit) {
            elements.push_back(currentElement);
            currentElement = "";
            timesSplit++;
        } else {
            currentElement += line[i];
        }

    }

    if(currentElement != "") {
        elements.push_back(currentElement);
    }

    return elements;
}