# JSON Parser & Generator (C++)

A lightweight, educational JSON parser and generator written in modern C++17. This project implements a complete JSON processing pipeline including lexical analysis, parsing, validation, pretty printing, and querying.

## Features

✨ **Core Features:**
- ✅ Parse JSON from files or strings
- ✅ Validate JSON structure and syntax
- ✅ Pretty print with configurable indentation
- ✅ Minify JSON (compact format)
- ✅ Query JSON data by path (dot + array index syntax, e.g. `settings.indentSize`, `features[1]`)
- ✅ Support for all JSON types (null, boolean, number, string, array, object)
- ✅ Detailed error messages with line/column + context snippet
- ✅ Unicode escape handling (`\uXXXX`, surrogate pairs)

## Project Structure

```
json-parser-cpp/
├── include/
│   ├── JsonValue.h
│   ├── JsonLexer.h
│   ├── JsonParser.h
│   ├── JsonPrinter.h
│   └── JsonPath.h          # Path query helper
├── src/
│   ├── JsonValue.cpp
│   ├── JsonLexer.cpp
│   ├── JsonParser.cpp
│   ├── JsonPrinter.cpp
│   ├── JsonPath.cpp
│   └── main.cpp
├── tests/
│   ├── test_lexer.cpp
│   ├── test_parser.cpp
│   ├── test_path.cpp
│   └── test_printer.cpp
├── examples/
│   └── example.json
├── .github/
│   └── workflows/
│       └── ci.yml
├── CONTRIBUTING.md
├── CODE_OF_CONDUCT.md
└── CMakeLists.txt
```

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest --output-on-failure    # run tests
```

## CLI Usage

```bash
./json-parser validate examples/example.json
./json-parser pretty examples/example.json
./json-parser minify examples/example.json
./json-parser query examples/example.json settings.indentSize
./json-parser query examples/example.json features[2]
```

## Query Path Syntax

- Dot for object keys: `settings.indentSize`
- Array index: `features[1]`
- Mixed: `nested.list[0].name`
- Returns first matching path or reports not found.

## Error Reporting

Errors show:
- Line / column
- Context line with caret

Example:
```
Error: Unexpected token at line 5, column 14
    "value": 01,
              ^
Reason: Leading zero in number is not allowed
```

## Unicode Support

String parser recognizes `\uXXXX` escapes, decodes surrogate pairs, and inserts UTF-8.

## Testing

Tests cover:
- Lexer tokens & edge cases (strings, escapes, unicode, invalid numbers)
- Parser correctness (objects, arrays, errors)
- Path queries (valid + invalid)
- Printer round-trip

Run: `ctest --output-on-failure`

## Roadmap

- [ ] Streaming parser
- [ ] JSONPath wildcards / recursive descent
- [ ] Schema validation
- [ ] Performance benchmarks
- [ ] Coverage + badge
- [ ] Fuzz testing

## License

MIT

---
Built for learning and testing C++.
