#include "JsonValue.h"

namespace json {

JsonValue::JsonValue() : type_(ValueType::NULL_TYPE), boolValue_(false), numberValue_(0.0) {}

JsonValue::JsonValue(bool value) : type_(ValueType::BOOLEAN), boolValue_(value), numberValue_(0.0) {}

JsonValue::JsonValue(double value) : type_(ValueType::NUMBER), boolValue_(false), numberValue_(value) {}

JsonValue::JsonValue(const std::string& value) : type_(ValueType::STRING), boolValue_(false), numberValue_(0.0), stringValue_(value) {}

JsonValue::JsonValue(const char* value) : type_(ValueType::STRING), boolValue_(false), numberValue_(0.0), stringValue_(value) {}

JsonValue JsonValue::makeNull() {
    return JsonValue();
}

JsonValue JsonValue::makeArray() {
    JsonValue val;
    val.type_ = ValueType::ARRAY;
    return val;
}

JsonValue JsonValue::makeObject() {
    JsonValue val;
    val.type_ = ValueType::OBJECT;
    return val;
}

bool JsonValue::asBool() const {
    if (type_ != ValueType::BOOLEAN) {
        throw std::runtime_error("JsonValue is not a boolean");
    }
    return boolValue_;
}

double JsonValue::asNumber() const {
    if (type_ != ValueType::NUMBER) {
        throw std::runtime_error("JsonValue is not a number");
    }
    return numberValue_;
}

const std::string& JsonValue::asString() const {
    if (type_ != ValueType::STRING) {
        throw std::runtime_error("JsonValue is not a string");
    }
    return stringValue_;
}

size_t JsonValue::size() const {
    if (type_ == ValueType::ARRAY) {
        return arrayValue_.size();
    } else if (type_ == ValueType::OBJECT) {
        return objectValue_.size();
    }
    throw std::runtime_error("JsonValue is not an array or object");
}

JsonValue& JsonValue::operator[](size_t index) {
    if (type_ != ValueType::ARRAY) {
        throw std::runtime_error("JsonValue is not an array");
    }
    if (index >= arrayValue_.size()) {
        throw std::out_of_range("Array index out of range");
    }
    return arrayValue_[index];
}

const JsonValue& JsonValue::operator[](size_t index) const {
    if (type_ != ValueType::ARRAY) {
        throw std::runtime_error("JsonValue is not an array");
    }
    if (index >= arrayValue_.size()) {
        throw std::out_of_range("Array index out of range");
    }
    return arrayValue_[index];
}

JsonValue& JsonValue::operator[](const std::string& key) {
    if (type_ != ValueType::OBJECT) {
        throw std::runtime_error("JsonValue is not an object");
    }
    return objectValue_[key];
}

const JsonValue& JsonValue::operator[](const std::string& key) const {
    if (type_ != ValueType::OBJECT) {
        throw std::runtime_error("JsonValue is not an object");
    }
    auto it = objectValue_.find(key);
    if (it == objectValue_.end()) {
        throw std::out_of_range("Key not found in object: " + key);
    }
    return it->second;
}

void JsonValue::push_back(const JsonValue& value) {
    if (type_ != ValueType::ARRAY) {
        throw std::runtime_error("JsonValue is not an array");
    }
    arrayValue_.push_back(value);
}

bool JsonValue::hasKey(const std::string& key) const {
    if (type_ != ValueType::OBJECT) {
        return false;
    }
    return objectValue_.find(key) != objectValue_.end();
}

const std::vector<JsonValue>& JsonValue::getArray() const {
    if (type_ != ValueType::ARRAY) {
        throw std::runtime_error("JsonValue is not an array");
    }
    return arrayValue_;
}

const std::map<std::string, JsonValue>& JsonValue::getObject() const {
    if (type_ != ValueType::OBJECT) {
        throw std::runtime_error("JsonValue is not an object");
    }
    return objectValue_;
}

} // namespace json
