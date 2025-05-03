#pragma once

#include <string>
#include <vector>


class TcpSocket {

public:

    TcpSocket(const std::string &ipAddress, const uint32_t portNumber);
    TcpSocket() = delete;

    void Bind();
    void Listen();
    void Accept();
    std::vector<uint8_t> ReceiveRequest();

private:

    void _Close();

    int mTcpSocketFileDescriptor = 0;
    int mAcceptFileDescriptor = 0;
    const std::string mMyAddress;
    const uint32_t mPortNumber;

};
