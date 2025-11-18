cmake_minimum_required(VERSION 3.15)
project(json-parser-cpp VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/JsonValue.cpp
    src/JsonLexer.cpp
    src/JsonParser.cpp
    src/JsonPrinter.cpp
    src/JsonPath.cpp
)

add_library(jsonlib ${SOURCES})

add_executable(json-parser src/main.cpp)
target_link_libraries(json-parser jsonlib)

if(MSVC)
    target_compile_options(jsonlib PRIVATE /W4)
    target_compile_options(json-parser PRIVATE /W4)
else()
    target_compile_options(jsonlib PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion)
    target_compile_options(json-parser PRIVATE -Wall -Wextra -pedantic -Wconversion -Wsign-conversion)
endif()

enable_testing()
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(json-tests ${TEST_SOURCES})
target_link_libraries(json-tests jsonlib)
add_test(NAME json_tests COMMAND json-tests)
