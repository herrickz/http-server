cmake_minimum_required(VERSION 3.15)
project(MyProject)

# Enable CTest for running tests
enable_testing()

# Find GTest (provided by Conan)
find_package(GTest REQUIRED)

# Add your test executable
add_executable(MyTests test_string_utils.cpp ${CMAKE_SOURCE_DIR}/src/StringUtils.cpp)

# Link GTest to the test executable
target_link_libraries(MyTests GTest::gtest GTest::gtest_main)
target_include_directories(MyTests PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Register the test with CTest (use the correct path)
add_test(NAME MyTests COMMAND $<TARGET_FILE:MyTests>)
