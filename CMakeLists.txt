cmake_minimum_required (VERSION 2.8)
project (embeddedCypher)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory (src)
add_subdirectory (tests)
enable_testing ()
add_test (NAME parserTestSuite COMMAND parserTestSuite)
add_dependencies(parserTestSuite parser)
add_dependencies(parserCLI parser)
