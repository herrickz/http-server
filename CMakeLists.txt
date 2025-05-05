cmake_minimum_required(VERSION 3.10.0)
project(http-server)

set(CXX_STANDARD_REQUIRED 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    http-server
    src/main.cpp
    src/StringUtils.cpp
    src/TcpSocket.cpp
    src/Logger.cpp
    src/ArgumentParser.cpp
)

target_compile_options(http-server PRIVATE
    -Wall
    -Wextra
    -Werror
)

target_include_directories(http-server PUBLIC include)

enable_testing()

add_subdirectory(test)
