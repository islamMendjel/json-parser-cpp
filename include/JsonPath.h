#ifndef JSON_PATH_H
#define JSON_PATH_H

#include "JsonValue.h"
#include <string>
#include <optional>
#include <vector>

namespace json {

// Splits a path like: a.b[2].c into segments: a, b, [2], c
std::vector<std::string> splitPath(const std::string& path);

// Query a JsonValue by path (dot + [index] tokens). Returns pointer or nullopt if not found.
std::optional<const JsonValue*> queryPath(const JsonValue& root, const std::string& path);

} // namespace json

#endif // JSON_PATH_H
