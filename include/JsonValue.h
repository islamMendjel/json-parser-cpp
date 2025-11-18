#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

namespace json {

enum class ValueType {
    NULL_TYPE,
    BOOLEAN,
    NUMBER,
    STRING,
    ARRAY,
    OBJECT
};

class JsonValue {
public:
    JsonValue();
    explicit JsonValue(bool value);
    explicit JsonValue(double value);
    explicit JsonValue(const std::string& value);
    explicit JsonValue(const char* value);
    
    static JsonValue makeNull();
    static JsonValue makeArray();
    static JsonValue makeObject();
    
    ValueType getType() const { return type_; }
    
    bool isNull() const { return type_ == ValueType::NULL_TYPE; }
    bool isBool() const { return type_ == ValueType::BOOLEAN; }
    bool isNumber() const { return type_ == ValueType::NUMBER; }
    bool isString() const { return type_ == ValueType::STRING; }
    bool isArray() const { return type_ == ValueType::ARRAY; }
    bool isObject() const { return type_ == ValueType::OBJECT; }
    
    bool asBool() const;
    double asNumber() const;
    const std::string& asString() const;
    
    size_t size() const;
    JsonValue& operator[](size_t index);
    const JsonValue& operator[](size_t index) const;
    
    JsonValue& operator[](const std::string& key);
    const JsonValue& operator[](const std::string& key) const;
    
    void push_back(const JsonValue& value);
    bool hasKey(const std::string& key) const;
    
    const std::vector<JsonValue>& getArray() const;
    const std::map<std::string, JsonValue>& getObject() const;
    
private:
    ValueType type_;
    bool boolValue_;
    double numberValue_;
    std::string stringValue_;
    std::vector<JsonValue> arrayValue_;
    std::map<std::string, JsonValue> objectValue_;
};

} // namespace json

#endif // JSON_VALUE_H
