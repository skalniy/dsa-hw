cmake_minimum_required(VERSION 3.0)

include(CTest)

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
# if(result)
#   message(FATAL_ERROR "Build step for googletest failed: ${result}")
# endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
# add_executable(example example.cpp)
# target_link_libraries(example gtest_main)
# add_test(NAME example_test COMMAND example)

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
