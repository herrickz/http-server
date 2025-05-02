cmake_minimum_required(VERSION 3.10.0)

set(CXX_STANDARD_REQUIRED 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(http-server)

add_executable(http-server src/main.cpp)

add_subdirectory(test)
