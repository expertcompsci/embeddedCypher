cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} parser)
 
add_executable(parserTestSuite ParserTestSuite.cpp)
target_link_libraries(parserTestSuite ${GTEST_LIBRARIES} parser pthread)

