cmake_minimum_required(VERSION 3.15)
project(MyProject)

enable_testing()

# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)  # usually auto-included if you used `conan install`

find_package(GTest REQUIRED)

add_executable(HttpTest test_string_utils.cpp ${CMAKE_SOURCE_DIR}/src/StringUtils.cpp)

target_link_libraries(HttpTest GTest::gtest GTest::gtest_main)
target_include_directories(HttpTest PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_test(NAME HttpTest COMMAND $<TARGET_FILE:HttpTest>)
