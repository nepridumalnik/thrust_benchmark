cmake_minimum_required(VERSION 3.22)
project(thrust_test)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
