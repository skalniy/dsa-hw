cmake_minimum_required(VERSION 3.0)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

include(CTest)

add_executable(STLWrapperTest STLWrapperUnitTest.cxx)
target_include_directories(STLWrapperTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(STLWrapperTest gtest_main)
target_link_libraries(STLWrapperTest stl_wrapper)
add_test(NAME stl_wrapper_test COMMAND STLWrapperTest)

add_executable(ChainTest ChainUnitTest.cxx)
target_include_directories(ChainTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(ChainTest gtest_main)
target_link_libraries(ChainTest chain)
add_test(NAME chain_test COMMAND ChainTest)

add_executable(DoubleHashTest DoubleHashUnitTest.cxx)
target_include_directories(DoubleHashTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(DoubleHashTest gtest_main)
target_link_libraries(DoubleHashTest double_hash)
add_test(NAME double_hash_test COMMAND DoubleHashTest)

add_executable(CuckooTest CuckooUnitTest.cxx)
target_include_directories(CuckooTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(CuckooTest gtest_main)
target_link_libraries(CuckooTest cuckoo)
add_test(NAME cuckoo_test COMMAND CuckooTest)

configure_file(HighloadUnitTest.py.in "${CMAKE_BINARY_DIR}/test/HighloadUnitTest.py")
add_test(
  NAME highload_test 
  COMMAND python3 "${CMAKE_BINARY_DIR}/test/HighloadUnitTest.py"
)