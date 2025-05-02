
#include <iostream>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <cassert>
#include <sstream>

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

/**
 * @param line: Line to split
 * @param delimiter: Delimiter to use when splitting the line
 * @param times: Amount of times to split the line by the delimiter (Default 0 (split all instances))
 */
std::vector<std::string> splitLineOnDelimiter(const std::string &line, const char delim, int times = 0) {

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

int main() {

    int tcpSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in myAddress;
    sockaddr_in peerAddress;

    memset(&myAddress, 0, sizeof(sockaddr_in));
    myAddress.sin_family = AF_INET;
    myAddress.sin_port = htons(9090);
    inet_aton("127.0.0.1", &myAddress.sin_addr);

    int bindReturnValue = bind(tcpSocketFileDescriptor, (const sockaddr *)&myAddress, sizeof(sockaddr_in));

    // errno just holds error number
    // need to use strerror to get the actual error string
    if(bindReturnValue == -1) {
        std::cout << "Bind failed: " << strerror(errno) << std::endl;
        return -1;
    }

    int listenReturnValue = listen(tcpSocketFileDescriptor, 10);

    if(listenReturnValue == -1) {
        std::cout << "Listen failed: " << strerror(errno) << std::endl;
        return -1;
    }

    socklen_t peerAddressSize = sizeof(peerAddress);

    int acceptFileDescriptor = accept(tcpSocketFileDescriptor, (sockaddr *) &peerAddress, &peerAddressSize);

    if(acceptFileDescriptor == -1) {
        std::cout << "Accept failed: " << strerror(errno) << std::endl;
        return -1;
    }

    char buffer[512];

    ssize_t receiveByteLength = recv(acceptFileDescriptor, buffer, 512, 0);

    if(receiveByteLength == -1) {
        std::cout << "Receive failed: " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "received: " << receiveByteLength << std::endl;

    int closeReturnValue = close(tcpSocketFileDescriptor);

    if(closeReturnValue == -1) {
        std::cout << "Close failed: " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << buffer << std::endl;

    std::string requestType = "";
    std::string path = "";

    std::vector<std::string> lineEntries;
    std::string currentEntry = "";

    // split the entire buffer into separate line entries
    for(int i = 0; i < receiveByteLength; i++) {

        if(buffer[i] == '\n') {
            lineEntries.push_back(currentEntry);
            currentEntry = "";
        } else {
            currentEntry += buffer[i];
        }

    }

    lineEntries.push_back(currentEntry);

    for(int i = 0; i < lineEntries.size(); i++) {

        const std::string &line = lineEntries[i];

        if(i == 0) { // Start Line
            std::vector<std::string> elements = splitLineOnDelimiter(line, ' ');

            HttpStartLine httpStartLine = getHttpStartLineFromStringList(elements);

            std::cout << httpStartLine << std::endl;
        }
    }


    // for(int i = 0; i < receiveByteLength; i++) {

    //     if(buffer[i] == ' ') {
    //         lineEntries.push_back(currentEntry);
    //         currentEntry = "";
    //     } else {

    //     }

    //     if(newlineCount == 0) {

    //     }

    // }

    return 0;
}