#include "JsonParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace json {

JsonParser::JsonParser(const std::string& input) : current_(0) {
    JsonLexer lexer(input);
    tokens_ = lexer.tokenize();
}

JsonValue JsonParser::parse() {
    if (tokens_.empty()) {
        throw std::runtime_error("No tokens to parse");
    }
    return parseValue();
}

JsonValue JsonParser::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    JsonParser parser(buffer.str());
    return parser.parse();
}

JsonValue JsonParser::parseValue() {
    const Token& token = peek();
    
    switch (token.type) {
        case TokenType::LEFT_BRACE:
            return parseObject();
        case TokenType::LEFT_BRACKET:
            return parseArray();
        case TokenType::STRING:
            advance();
            return JsonValue(token.value);
        case TokenType::NUMBER:
            advance();
            return JsonValue(std::stod(token.value));
        case TokenType::TRUE:
            advance();
            return JsonValue(true);
        case TokenType::FALSE:
            advance();
            return JsonValue(false);
        case TokenType::NULL_TOKEN:
            advance();
            return JsonValue::makeNull();
        default:
            throw std::runtime_error("Unexpected token at line " + 
                                   std::to_string(token.line) + 
                                   ", column " + std::to_string(token.column));
    }
}

JsonValue JsonParser::parseObject() {
    expect(TokenType::LEFT_BRACE, "Expected '{'");
    
    JsonValue obj = JsonValue::makeObject();
    
    if (check(TokenType::RIGHT_BRACE)) {
        advance();
        return obj;
    }
    
    while (true) {
        expect(TokenType::STRING, "Expected string key");
        std::string key = tokens_[current_ - 1].value;
        
        expect(TokenType::COLON, "Expected ':' after key");
        
        JsonValue value = parseValue();
        obj[key] = value;
        
        if (!match(TokenType::COMMA)) {
            break;
        }
    }
    
    expect(TokenType::RIGHT_BRACE, "Expected '}'");
    return obj;
}

JsonValue JsonParser::parseArray() {
    expect(TokenType::LEFT_BRACKET, "Expected '['");
    
    JsonValue arr = JsonValue::makeArray();
    
    if (check(TokenType::RIGHT_BRACKET)) {
        advance();
        return arr;
    }
    
    while (true) {
        arr.push_back(parseValue());
        
        if (!match(TokenType::COMMA)) {
            break;
        }
    }
    
    expect(TokenType::RIGHT_BRACKET, "Expected ']'");
    return arr;
}

const Token& JsonParser::peek() const {
    return tokens_[current_];
}

const Token& JsonParser::advance() {
    if (!isAtEnd()) current_++;
    return tokens_[current_ - 1];
}

bool JsonParser::check(TokenType type) const {
    if (current_ >= tokens_.size()) return false;
    return peek().type == type;
}

bool JsonParser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

void JsonParser::expect(TokenType type, const std::string& message) {
    if (!check(type)) {
        throw std::runtime_error(message);
    }
    advance();
}

bool JsonParser::isAtEnd() const {
    return current_ >= tokens_.size() || peek().type == TokenType::END_OF_FILE;
}

} // namespace json
