cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_library(stl_wrapper stl_wrapper.cxx)
target_include_directories(stl_wrapper PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(double_hash double_hash.cxx)
target_include_directories(double_hash PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_library(cuckoo cuckoo.cxx)
target_include_directories(cuckoo PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME} main.cxx)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} stl_wrapper)
