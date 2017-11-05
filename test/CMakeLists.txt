cmake_minimum_required(VERSION 3.8)

find_package(GTest REQUIRED)

include(CTest)

add_executable(STLWrapperTest STLWrapperUnitTest.cxx)

target_include_directories(STLWrapperTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(STLWrapperTest GTest::GTest GTest::Main)
target_link_libraries(STLWrapperTest stl_wrapper)

GTEST_ADD_TESTS(STLWrapperTest "" AUTO)
