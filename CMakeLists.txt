cmake_minimum_required(VERSION 3.10.0)

set(CXX_STANDARD_REQUIRED 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(http-server)

add_executable(
    http-server
    src/main.cpp
    src/StringUtils.cpp
    src/TcpSocket.cpp
)

target_include_directories(http-server PUBLIC include)

enable_testing()

add_subdirectory(test)
