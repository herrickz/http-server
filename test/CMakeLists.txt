cmake_minimum_required(VERSION 3.15)
project(MyProject)

enable_testing()

# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)  # usually auto-included if you used `conan install`

find_package(GTest REQUIRED)

add_executable(
    HttpTest
    test_string_utils.cpp
    test_argument_parser.cpp
    test_file_reader.cpp
    ${CMAKE_SOURCE_DIR}/src/StringUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/ArgumentParser.cpp
    ${CMAKE_SOURCE_DIR}/src/Logger.cpp
    ${CMAKE_SOURCE_DIR}/src/FileReader.cpp
)

target_link_libraries(HttpTest GTest::gtest GTest::gtest_main)
target_include_directories(HttpTest PUBLIC ${CMAKE_SOURCE_DIR}/include)

configure_file(data/myfile.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(NAME HttpTest COMMAND $<TARGET_FILE:HttpTest>)
