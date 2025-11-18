# JSON Parser & Generator (C++)

A lightweight, educational JSON parser and generator written in modern C++17. This project implements a complete JSON processing pipeline including lexical analysis, parsing, validation, pretty printing, and querying.

## Features

✨ **Core Features:**
- ✅ Parse JSON from files or strings
- ✅ Validate JSON structure and syntax
- ✅ Pretty print with configurable indentation
- ✅ Minify JSON (compact format)
- ✅ Query JSON data by key
- ✅ Support for all JSON types (null, boolean, number, string, array, object)
- ✅ Detailed error messages with line/column information

## Project Structure

```
json-parser-cpp/
├── include/          # Header files
│   ├── JsonValue.h   # JSON value representation
│   ├── JsonLexer.h   # Tokenizer
│   ├── JsonParser.h  # Parser
│   └── JsonPrinter.h # Pretty printer
├── src/              # Implementation files
│   ├── JsonValue.cpp
│   ├── JsonLexer.cpp
│   ├── JsonParser.cpp
│   ├── JsonPrinter.cpp
│   └── main.cpp      # CLI application
├── examples/         # Example JSON files
└── CMakeLists.txt    # Build configuration
```

## Building

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.15 or higher

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/islamMendjel/json-parser-cpp.git
cd json-parser-cpp

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .
```

## Usage

### Command Line Interface

```bash
# Parse and validate a JSON file
./json-parser parse examples/example.json

# Pretty print JSON
./json-parser pretty examples/example.json

# Minify JSON
./json-parser minify examples/example.json

# Validate JSON syntax
./json-parser validate examples/example.json

# Query a value by key
./json-parser query examples/example.json name
```

### Programmatic Usage

```cpp
#include "JsonParser.h"
#include "JsonPrinter.h"

// Parse from string
json::JsonParser parser(R"({"name": "test", "value": 42})");
json::JsonValue root = parser.parse();

// Access values
std::string name = root["name"].asString();
double value = root["value"].asNumber();

// Parse from file
json::JsonValue data = json::JsonParser::parseFile("data.json");

// Pretty print
std::string output = json::JsonPrinter::print(root, true, 2);
std::cout << output << std::endl;

// Create JSON programmatically
json::JsonValue obj = json::JsonValue::makeObject();
obj["name"] = json::JsonValue("John");
obj["age"] = json::JsonValue(30.0);

json::JsonValue arr = json::JsonValue::makeArray();
arr.push_back(json::JsonValue(1.0));
arr.push_back(json::JsonValue(2.0));
obj["numbers"] = arr;
```

## Architecture

### 1. **Lexer (Tokenizer)**
Breaks raw JSON text into tokens:
- Identifies symbols: `{`, `}`, `[`, `]`, `:`, `,`
- Extracts strings, numbers, keywords (true, false, null)
- Tracks line and column for error reporting

### 2. **Parser**
Builds a tree structure from tokens:
- Recursive descent parser
- Validates JSON grammar
- Creates `JsonValue` objects

### 3. **JsonValue**
Represents JSON data:
- Type-safe value wrapper
- Supports all JSON types
- Easy access with `[]` operator

### 4. **Printer**
Serializes JSON back to text:
- Pretty printing with indentation
- Minified output
- String escaping

## Learning Path

This project teaches:
1. **Lexical Analysis** - Breaking text into tokens
2. **Parsing** - Grammar and syntax trees
3. **Data Structures** - Trees, variants, recursive structures
4. **Modern C++** - Smart pointers, STL containers, exceptions
5. **API Design** - Clean interfaces, error handling
6. **CLI Development** - Command-line argument parsing

## Roadmap

- [ ] Unicode support (UTF-8)
- [ ] JSONPath query language
- [ ] Schema validation
- [ ] Streaming parser for large files
- [ ] Performance optimizations
- [ ] Unit tests
- [ ] Benchmarks

## Examples

**Input JSON:**
```json
{"name":"test","values":[1,2,3],"nested":{"key":"value"}}
```

**Pretty Printed:**
```json
{
  "name": "test",
  "values": [
    1,
    2,
    3
  ],
  "nested": {
    "key": "value"
  }
}
```

## Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest features
- Submit pull requests
- Improve documentation

## License

MIT License - feel free to use this for learning and projects!

## Author

**Islam Mendjel** ([@islamMendjel](https://github.com/islamMendjel))

---

Built with ❤️ for learning C++ and understanding how parsers work!
