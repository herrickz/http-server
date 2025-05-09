
#include "gtest/gtest.h"

#include "HttpParser.h"

TEST(HttpParser, parseHeaderReturnsThreeHeaders) {

    const std::string httpContents =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: curl/8.4.0\r\n"
        "Accept: */*\r\n"
        "\r\n";

    std::vector<uint8_t> bytes;

    bytes.resize(httpContents.size());

    for(uint32_t i = 0; i < httpContents.size(); i++) {
        bytes[i] = httpContents[i];
    }

    HttpParser httpParser(bytes);

    std::vector<HttpHeader> headers = httpParser.GetHeaders();

    EXPECT_EQ(headers.size(), 3);

}

TEST(HttpParser, parseHeaderGetRequestOnRoot) {

    const std::string httpContents =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: curl/8.4.0\r\n"
        "Accept: */*\r\n"
        "\r\n";

    std::vector<uint8_t> bytes;

    bytes.resize(httpContents.size());

    for(uint32_t i = 0; i < httpContents.size(); i++) {
        bytes[i] = httpContents[i];
    }

    HttpParser httpParser(bytes);

    HttpStartLine httpStartLine = httpParser.GetStartLine();

    EXPECT_EQ(httpStartLine.httpVersion, "HTTP/1.1");
    EXPECT_EQ(httpStartLine.method, HttpMethod::GET);
    EXPECT_EQ(httpStartLine.path, "/");

}


TEST(HttpHeader, getNameReturnsContentType) {

    const std::string headerContent = "content-type: text/html; charset=UTF-8";

    HttpHeader httpHeader(headerContent);

    EXPECT_EQ(httpHeader.GetName(), "content-type");
}

TEST(HttpHeadr, getValueReturnsTextHtml) {
    const std::string headerContent = "content-type: text/html; charset=UTF-8";

    HttpHeader httpHeader(headerContent);

    EXPECT_EQ(httpHeader.GetValue(), "text/html; charset=UTF-8");

}