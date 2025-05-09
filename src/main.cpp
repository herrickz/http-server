
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <vector>

#include "StringUtils.h"
#include "Logger.h"
#include "TcpSocket.h"
#include "ArgumentParser.h"
#include "HttpParser.h"

std::ostream &operator<<(std::ostream &stream, const HttpStartLine &httpStartLine) {

    stream << "HttpStartLine" << std::endl;
    stream << "    Method: " << httpStartLine.method << " (" << httpStartLine.methodName << ")" << std::endl;
    stream << "    path: " << httpStartLine.path << std::endl;
    stream << "    httpVersion: " << httpStartLine.httpVersion << std::endl;

    return stream;
}

int main(int argc, char **argv) {

    ArgumentParser argumentParser;

    argumentParser.AddArgument("p", "port");
    argumentParser.AddArgument("fp", "file-path");

    argumentParser.ParseArguments(argc, argv);

    const std::string filePath = argumentParser.GetValue<std::string>("fp");
    const int port = argumentParser.GetValue<int>("p");

    LOG_INFO("Running on port %d and file path: %s", port, filePath.c_str());

    TcpSocket tcpSocket("127.0.0.1", 9090);

    tcpSocket.Bind();
    tcpSocket.Listen();

    while(true) {

        tcpSocket.Accept();
        std::vector<uint8_t> bytes = tcpSocket.ReceiveRequest();

        HttpParser httpParser(bytes);

        LOG_INFO(
            "Method: %s | Path: %s | Version: %s",
            httpParser.GetStartLine().methodName.c_str(),
            httpParser.GetStartLine().path.c_str(),
            httpParser.GetStartLine().httpVersion.c_str()
        );
    }

    return 0;
}