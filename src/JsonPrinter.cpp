#include "JsonPrinter.h"
#include <sstream>

namespace json {

std::string JsonPrinter::print(const JsonValue& value, bool pretty, int indent) {
    std::string output;
    printValue(value, output, pretty, indent, 0);
    return output;
}

void JsonPrinter::printValue(const JsonValue& value, std::string& output, bool pretty, int indent, int currentIndent) {
    switch (value.getType()) {
        case ValueType::NULL_TYPE:
            output += "null";
            break;
            
        case ValueType::BOOLEAN:
            output += value.asBool() ? "true" : "false";
            break;
            
        case ValueType::NUMBER: {
            std::ostringstream oss;
            oss << value.asNumber();
            output += oss.str();
            break;
        }
            
        case ValueType::STRING:
            output += "\"" + escapeString(value.asString()) + "\"";
            break;
            
        case ValueType::ARRAY: {
            output += "[";
            const auto& arr = value.getArray();
            
            if (!arr.empty()) {
                if (pretty) {
                    output += "\n";
                }
                
                for (size_t i = 0; i < arr.size(); ++i) {
                    if (pretty) {
                        printIndent(output, currentIndent + indent);
                    }
                    
                    printValue(arr[i], output, pretty, indent, currentIndent + indent);
                    
                    if (i < arr.size() - 1) {
                        output += ",";
                    }
                    
                    if (pretty) {
                        output += "\n";
                    }
                }
                
                if (pretty) {
                    printIndent(output, currentIndent);
                }
            }
            
            output += "]";
            break;
        }
            
        case ValueType::OBJECT: {
            output += "{";
            const auto& obj = value.getObject();
            
            if (!obj.empty()) {
                if (pretty) {
                    output += "\n";
                }
                
                size_t i = 0;
                for (const auto& pair : obj) {
                    if (pretty) {
                        printIndent(output, currentIndent + indent);
                    }
                    
                    output += "\"" + escapeString(pair.first) + "\":";
                    
                    if (pretty) {
                        output += " ";
                    }
                    
                    printValue(pair.second, output, pretty, indent, currentIndent + indent);
                    
                    if (i < obj.size() - 1) {
                        output += ",";
                    }
                    
                    if (pretty) {
                        output += "\n";
                    }
                    
                    ++i;
                }
                
                if (pretty) {
                    printIndent(output, currentIndent);
                }
            }
            
            output += "}";
            break;
        }
    }
}

void JsonPrinter::printIndent(std::string& output, int spaces) {
    output.append(spaces, ' ');
}

std::string JsonPrinter::escapeString(const std::string& str) {
    std::string escaped;
    for (char c : str) {
        switch (c) {
            case '"': escaped += "\\\""; break;
            case '\': escaped += "\\\\"; break;
            case '\b': escaped += "\\b"; break;
            case '\f': escaped += "\\f"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default: escaped += c; break;
        }
    }
    return escaped;
}

} // namespace json
