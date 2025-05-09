
#include "HttpParser.h"
#include "StringUtils.h"
#include "Logger.h"

#include <cassert>
#include <sstream>

#define assertm(exp, msg) assert((void(msg), exp))

HttpStartLine getHttpStartLineFromStringList(const std::vector<std::string> &elements) {

    assertm(elements.size() == 3, "Size of elements != 3. Actual size");

    HttpStartLine httpStartLine;

    if(elements[0] == "GET") {
        httpStartLine.method = HttpMethod::GET;
    } else if(elements[0] == "HEAD") {
        httpStartLine.method = HttpMethod::HEAD;
    } else if(elements[0] == "POST") {
        httpStartLine.method = HttpMethod::POST;
    } else if(elements[0] == "PUT") {
        httpStartLine.method = HttpMethod::PUT;
    } else if(elements[0] == "DELETE") {
        httpStartLine.method = HttpMethod::DELETE;
    } else if(elements[0] == "CONNECT") {
        httpStartLine.method = HttpMethod::CONNECT;
    } else if(elements[0] == "OPTIONS") {
        httpStartLine.method = HttpMethod::OPTIONS;
    } else if(elements[0] == "TRACE") {
        httpStartLine.method = HttpMethod::TRACE;
    } else if(elements[0] == "PATCH") {
        httpStartLine.method = HttpMethod::PATCH;
    } else {
        std::stringstream ss;

        ss << "Unrecognized http method: " << elements[0] << std::endl;

        assertm(false, ss.str());
    }

    httpStartLine.methodName = elements[0];
    httpStartLine.path = elements[1];
    httpStartLine.httpVersion = elements[2];

    return httpStartLine;
}

/**
 * <header-name>: <header-value>
 */
HttpHeader::HttpHeader(const std::string &httpHeaderLine) {

    size_t firstColonPosition = httpHeaderLine.find_first_of(':');

    mName = httpHeaderLine.substr(0, firstColonPosition);
    mValue = httpHeaderLine.substr(firstColonPosition + 2, httpHeaderLine.size());

}

std::string HttpHeader::GetName() {
    return mName;
}

std::string HttpHeader::GetValue() {
    return mValue;
}

HttpParser::HttpParser(const std::vector<uint8_t> &bytes) {

    std::vector<std::string> lineEntries;
    std::string currentEntry = "";

    for(size_t i = 0; i < bytes.size(); i++) {

        if(bytes[i] == '\r') {
            lineEntries.push_back(currentEntry);
            currentEntry = "";
            i++; // skip new line
        } else {
            currentEntry += bytes[i];
        }

    }

    lineEntries.push_back(currentEntry);

    bool encounteredEmptyLine = false;
    std::vector<std::string> body;

    for(size_t i = 0; i < lineEntries.size(); i++) {

        const std::string &line = lineEntries[i];

        if(i == 0) { // Start Line
            std::vector<std::string> elements = splitLineOnDelimiter(line, ' ');

            mStartLine = getHttpStartLineFromStringList(elements);

        } else {

            if(!encounteredEmptyLine && line != "") {
                mHeaders.push_back(HttpHeader(line));
            } else if(encounteredEmptyLine) {
                body.push_back(line);
            }

            if(!encounteredEmptyLine && line == "") {
                encounteredEmptyLine = true;
            }

        }
    }
}

HttpStartLine HttpParser::GetStartLine() {
    return mStartLine;
}

std::vector<HttpHeader> HttpParser::GetHeaders() {
    return mHeaders;
}
