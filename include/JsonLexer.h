#ifndef JSON_LEXER_H
#define JSON_LEXER_H

#include <string>
#include <vector>

namespace json {

enum class TokenType {
    LEFT_BRACE,    // {
    RIGHT_BRACE,   // }
    LEFT_BRACKET,  // [
    RIGHT_BRACKET, // ]
    COLON,         // :
    COMMA,         // ,
    STRING,
    NUMBER,
    TRUE,
    FALSE,
    NULL_TOKEN,
    END_OF_FILE,
    INVALID
};

struct Token {
    TokenType type;
    std::string value;
    size_t line;
    size_t column;
    
    Token(TokenType t, const std::string& v = "", size_t l = 0, size_t c = 0)
        : type(t), value(v), line(l), column(c) {}
};

class JsonLexer {
public:
    explicit JsonLexer(const std::string& input);
    
    std::vector<Token> tokenize();
    
private:
    void skipWhitespace();
    Token nextToken();
    Token parseString();
    Token parseNumber();
    Token parseKeyword();
    
    char peek() const;
    char advance();
    bool isAtEnd() const;
    
    std::string input_;
    size_t current_;
    size_t line_;
    size_t column_;
};

} // namespace json

#endif // JSON_LEXER_H
