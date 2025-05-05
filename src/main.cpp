
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <vector>
#include <cassert>
#include <sstream>

#include "StringUtils.h"
#include "Logger.h"
#include "TcpSocket.h"
#include "ArgumentParser.h"

#define assertm(exp, msg) assert((void(msg), exp))

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

std::ostream &operator<<(std::ostream &stream, const HttpStartLine &httpStartLine) {

    stream << "HttpStartLine" << std::endl;
    stream << "    Method: " << httpStartLine.method << " (" << httpStartLine.methodName << ")" << std::endl;
    stream << "    path: " << httpStartLine.path << std::endl;
    stream << "    httpVersion: " << httpStartLine.httpVersion << std::endl;

    return stream;
}

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

int main(int argc, char **argv) {

    ArgumentParser argumentParser;

    argumentParser.ParseArguments(argc, argv);

    LOG_INFO("%d: Lets go", 1);

    TcpSocket tcpSocket("127.0.0.1", 9090);

    tcpSocket.Bind();
    tcpSocket.Listen();

    while(true) {

        tcpSocket.Accept();
        std::vector<uint8_t> bytes = tcpSocket.ReceiveRequest();

        std::cout << "Received: " << bytes.size() << std::endl;

        std::vector<std::string> lineEntries;
        std::string currentEntry = "";

        // split the entire buffer into separate line entries
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
        std::vector<std::string> headers;
        std::vector<std::string> body;

        for(size_t i = 0; i < lineEntries.size(); i++) {

            const std::string &line = lineEntries[i];

            if(i == 0) { // Start Line
                std::vector<std::string> elements = splitLineOnDelimiter(line, ' ');

                HttpStartLine httpStartLine = getHttpStartLineFromStringList(elements);

                std::cout << httpStartLine << std::endl;
            } else {

                if(!encounteredEmptyLine && line != "") {
                    headers.push_back(line);
                } else if(encounteredEmptyLine) {
                    body.push_back(line);
                }

                if(!encounteredEmptyLine && line == "") {
                    encounteredEmptyLine = true;
                    std::cout << "Encountered empty line" << std::endl;
                }

            }
        }

        for(auto header : headers) {
            std::cout << "HEADER: " << header << std::endl;
        }

        std::cout << "Body" << std::endl;

        for(auto line : body) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}