#include "JsonLexer.h"
#include <cctype>
#include <stdexcept>

namespace json {

JsonLexer::JsonLexer(const std::string& input)
    : input_(input), current_(0), line_(1), column_(1) {}

std::vector<Token> JsonLexer::tokenize() {
    std::vector<Token> tokens;
    
    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;
        
        Token token = nextToken();
        if (token.type == TokenType::INVALID) {
            throw std::runtime_error("Invalid token at line " + std::to_string(line_) + 
                                   ", column " + std::to_string(column_));
        }
        tokens.push_back(token);
    }
    
    tokens.push_back(Token(TokenType::END_OF_FILE, "", line_, column_));
    return tokens;
}

void JsonLexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r') {
            advance();
        } else if (c == '\n') {
            advance();
            line_++;
            column_ = 1;
        } else {
            break;
        }
    }
}

Token JsonLexer::nextToken() {
    char c = peek();
    size_t tokenLine = line_;
    size_t tokenColumn = column_;
    
    switch (c) {
        case '{': advance(); return Token(TokenType::LEFT_BRACE, "{", tokenLine, tokenColumn);
        case '}': advance(); return Token(TokenType::RIGHT_BRACE, "}", tokenLine, tokenColumn);
        case '[': advance(); return Token(TokenType::LEFT_BRACKET, "[", tokenLine, tokenColumn);
        case ']': advance(); return Token(TokenType::RIGHT_BRACKET, "]", tokenLine, tokenColumn);
        case ':': advance(); return Token(TokenType::COLON, ":", tokenLine, tokenColumn);
        case ',': advance(); return Token(TokenType::COMMA, ",", tokenLine, tokenColumn);
        case '"': return parseString();
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return parseNumber();
        case 't': case 'f': case 'n':
            return parseKeyword();
        default:
            return Token(TokenType::INVALID, "", tokenLine, tokenColumn);
    }
}

Token JsonLexer::parseString() {
    size_t tokenLine = line_;
    size_t tokenColumn = column_;
    std::string value;
    
    advance(); // Skip opening quote
    
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\') {
            advance();
            if (isAtEnd()) {
                throw std::runtime_error("Unterminated string");
            }
            char escaped = advance();
            switch (escaped) {
                case '"': value += '"'; break;
                case '\': value += '\'; break;
                case '/': value += '/'; break;
                case 'b': value += '\b'; break;
                case 'f': value += '\f'; break;
                case 'n': value += '\n'; break;
                case 'r': value += '\r'; break;
                case 't': value += '\t'; break;
                default: value += escaped; break;
            }
        } else {
            value += advance();
        }
    }
    
    if (isAtEnd()) {
        throw std::runtime_error("Unterminated string");
    }
    
    advance(); // Skip closing quote
    return Token(TokenType::STRING, value, tokenLine, tokenColumn);
}

Token JsonLexer::parseNumber() {
    size_t tokenLine = line_;
    size_t tokenColumn = column_;
    std::string value;
    
    if (peek() == '-') {
        value += advance();
    }
    
    while (!isAtEnd() && (std::isdigit(peek()) || peek() == '.' || peek() == 'e' || peek() == 'E' || peek() == '+' || peek() == '-')) {
        value += advance();
    }
    
    return Token(TokenType::NUMBER, value, tokenLine, tokenColumn);
}

Token JsonLexer::parseKeyword() {
    size_t tokenLine = line_;
    size_t tokenColumn = column_;
    std::string value;
    
    while (!isAtEnd() && std::isalpha(peek())) {
        value += advance();
    }
    
    if (value == "true") {
        return Token(TokenType::TRUE, value, tokenLine, tokenColumn);
    } else if (value == "false") {
        return Token(TokenType::FALSE, value, tokenLine, tokenColumn);
    } else if (value == "null") {
        return Token(TokenType::NULL_TOKEN, value, tokenLine, tokenColumn);
    }
    
    return Token(TokenType::INVALID, value, tokenLine, tokenColumn);
}

char JsonLexer::peek() const {
    if (isAtEnd()) return '\0';
    return input_[current_];
}

char JsonLexer::advance() {
    column_++;
    return input_[current_++];
}

bool JsonLexer::isAtEnd() const {
    return current_ >= input_.length();
}

} // namespace json
