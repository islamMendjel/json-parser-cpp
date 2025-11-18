#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "JsonValue.h"
#include "JsonLexer.h"
#include <vector>
#include <string>

namespace json {

class JsonParser {
public:
    explicit JsonParser(const std::string& input);
    
    JsonValue parse();
    
    static JsonValue parseFile(const std::string& filename);
    
private:
    JsonValue parseValue();
    JsonValue parseObject();
    JsonValue parseArray();
    
    const Token& peek() const;
    const Token& advance();
    bool check(TokenType type) const;
    bool match(TokenType type);
    void expect(TokenType type, const std::string& message);
    bool isAtEnd() const;

    std::vector<Token> tokens_;
    size_t current_;
};

} // namespace json

#endif // JSON_PARSER_H
