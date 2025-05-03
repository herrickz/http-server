
#include "TcpSocket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <sstream>

TcpSocket::TcpSocket(const std::string &ipAddress, const uint32_t portNumber):
    mMyAddress(ipAddress), mPortNumber(portNumber) {
}

void TcpSocket::Bind() {

    mTcpSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in myAddress;

    memset(&myAddress, 0, sizeof(sockaddr_in));
    myAddress.sin_family = AF_INET;
    myAddress.sin_port = htons(9090);
    inet_aton("127.0.0.1", &myAddress.sin_addr);

    int bindReturnValue = bind(mTcpSocketFileDescriptor, (const sockaddr *)&myAddress, sizeof(sockaddr_in));

    // errno just holds error number
    // need to use strerror to get the actual error string
    if(bindReturnValue == -1) {
        std::stringstream ss;
        ss << "Bind failed: " << strerror(errno);
        throw std::runtime_error(ss.str());
    }
}

void TcpSocket::Listen() {
    int listenReturnValue = listen(mTcpSocketFileDescriptor, 10);

    if(listenReturnValue == -1) {
        std::stringstream ss;
        ss << "Listen failed: " << strerror(errno);
        throw std::runtime_error(ss.str());
    }

}

void TcpSocket::Accept() {
    sockaddr_in peerAddress;

    socklen_t peerAddressSize = sizeof(peerAddress);

    mAcceptFileDescriptor = accept(mTcpSocketFileDescriptor, (sockaddr *) &peerAddress, &peerAddressSize);

    if(mAcceptFileDescriptor == -1) {
        std::stringstream ss;
        ss << "Accept failed: " << strerror(errno);
        throw std::runtime_error(ss.str());
    }
}

std::vector<uint8_t> TcpSocket::ReceiveRequest() {
    std::vector<uint8_t> bytes;

    const uint32_t MAX_RECEIVE_SIZE = 65536;

    char buffer[MAX_RECEIVE_SIZE];

    ssize_t receiveByteLength = recv(mAcceptFileDescriptor, buffer, MAX_RECEIVE_SIZE, 0);

    while(
        receiveByteLength != -1
        && receiveByteLength == MAX_RECEIVE_SIZE
    ) {

        bytes.insert(bytes.end(), buffer, buffer + receiveByteLength);

        receiveByteLength = recv(mAcceptFileDescriptor, buffer, MAX_RECEIVE_SIZE, 0);
    }

    if(receiveByteLength > 0) {
        bytes.insert(bytes.end(), buffer, buffer + receiveByteLength);
    }

    if(receiveByteLength == -1) {
        std::cout << "Receive failed: " << strerror(errno) << std::endl;
        return bytes;
    }

    const char *reply = "HTTP/1.1 200 Success\r\n"
    "Server: Hello\r\n"
    "Connection: close\r\n"
    "Content-Length: 0\r\n";

    send(mAcceptFileDescriptor, reply, strlen(reply), 0);

    close(mAcceptFileDescriptor);

    return bytes;
}

void TcpSocket::_Close() {

    int closeReturnValue = close(mTcpSocketFileDescriptor);

    if(closeReturnValue == -1) {
        std::stringstream ss;
        ss << "Close failed: " << strerror(errno);
        throw std::runtime_error(ss.str());
    }

}
