cmake_minimum_required(VERSION 3.0)

project(DSA-HW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory (src)

enable_testing()
add_subdirectory (test)

add_subdirectory (scripts)
