cmake_minimum_required(VERSION 3.8)

project(DSA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_subdirectory (src)
add_subdirectory (test)
