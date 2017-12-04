cmake_minimum_required(VERSION 3.8)

find_package(GTest REQUIRED)

include(CTest)

add_executable(STLWrapperTest STLWrapperUnitTest.cxx)
target_include_directories(STLWrapperTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(STLWrapperTest GTest::GTest GTest::Main)
target_link_libraries(STLWrapperTest stl_wrapper)
GTEST_ADD_TESTS(STLWrapperTest "" AUTO)

add_executable(ChainTest ChainUnitTest.cxx)
target_include_directories(ChainTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(ChainTest GTest::GTest GTest::Main)
target_link_libraries(ChainTest chain)
GTEST_ADD_TESTS(ChainTest "" AUTO)

add_executable(DoubleHashTest DoubleHashUnitTest.cxx)
target_include_directories(DoubleHashTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(DoubleHashTest GTest::GTest GTest::Main)
target_link_libraries(DoubleHashTest double_hash)
GTEST_ADD_TESTS(DoubleHashTest "" AUTO)

add_executable(CuckooTest CuckooUnitTest.cxx)
target_include_directories(CuckooTest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(CuckooTest GTest::GTest GTest::Main)
target_link_libraries(CuckooTest cuckoo)
GTEST_ADD_TESTS(CuckooTest "" AUTO)
