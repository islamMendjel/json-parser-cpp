cmake_minimum_required(VERSION 3.15)
project(json-parser-cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/JsonValue.cpp
    src/JsonLexer.cpp
    src/JsonParser.cpp
    src/JsonPrinter.cpp
)

# Create library
add_library(jsonlib ${SOURCES})

# Main executable
add_executable(json-parser src/main.cpp)
target_link_libraries(json-parser jsonlib)

# Enable warnings
if(MSVC)
    target_compile_options(jsonlib PRIVATE /W4)
else()
    target_compile_options(jsonlib PRIVATE -Wall -Wextra -pedantic)
endif()
