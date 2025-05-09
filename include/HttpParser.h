#pragma once

#include <string>
#include <vector>

enum HttpMethod {
    GET = 0,
    HEAD = 1,
    POST = 2,
    PUT = 3,
    DELETE = 4,
    CONNECT = 5,
    OPTIONS = 6,
    TRACE = 7,
    PATCH = 8
};

struct HttpStartLine {
    HttpMethod method;
    std::string methodName;
    std::string path;
    std::string httpVersion;
};

class HttpHeader {

public:

    HttpHeader(const std::string &headerLine);

    std::string GetName();
    std::string GetValue();

private:

    std::string mName;
    std::string mValue;

};

class HttpParser {

public:

    HttpParser(const std::vector<uint8_t> &bytes);

    std::vector<HttpHeader> GetHeaders();
    HttpStartLine GetStartLine();

private:

    std::vector<HttpHeader> mHeaders;
    HttpStartLine mStartLine;

};