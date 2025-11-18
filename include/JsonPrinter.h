#ifndef JSON_PRINTER_H
#define JSON_PRINTER_H

#include "JsonValue.h"
#include <string>

namespace json {

class JsonPrinter {
public:
    static std::string print(const JsonValue& value, bool pretty = false, int indent = 2);
    
private:
    static void printValue(const JsonValue& value, std::string& output, bool pretty, int indent, int currentIndent);
    static void printIndent(std::string& output, int spaces);
    static std::string escapeString(const std::string& str);
};

} // namespace json

#endif // JSON_PRINTER_H
