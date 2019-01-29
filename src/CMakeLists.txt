set(CMAKE_CXX_STANDARD 11)

include_directories(parser scanner cli)
add_library(parser scanner/lex.cc parser/parse.cc)
target_include_directories (parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/parser)

add_executable(parserCLI cli/parserCLI.cc)
target_link_libraries(parserCLI LINK_PUBLIC parser)
