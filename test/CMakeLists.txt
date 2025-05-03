cmake_minimum_required(VERSION 3.15)
project(MyProject)

enable_testing()

# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)  # usually auto-included if you used `conan install`

find_package(GTest REQUIRED)

add_executable(MyTests test_string_utils.cpp ${CMAKE_SOURCE_DIR}/src/StringUtils.cpp)

target_link_libraries(MyTests GTest::gtest GTest::gtest_main)
target_include_directories(MyTests PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_test(NAME MyTests COMMAND $<TARGET_FILE:MyTests>)
