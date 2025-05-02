

cmake_minimum_required(VERSION 3.15)
project(MyTests)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

enable_testing()

add_executable(my_tests test_string_utils.cpp)
target_link_libraries(my_tests ${CONAN_LIBS})

add_test(NAME MyGTestSuite COMMAND my_tests)
