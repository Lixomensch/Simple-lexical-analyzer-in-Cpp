#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// Definição dos tipos de tokens
enum class TokenType
{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    PUNCTUATION,
    INTEGER,
    FLOAT,
    STRING
};

// Estrutura para armazenar um token
struct Token
{
    std::string value;
    TokenType type;
};

class Lexer
{
public:
    Lexer(const std::string &source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t index;
    std::vector<Token> tokens;

    void processToken();
    TokenType classifyToken(const std::string &token);
    bool isNumber(const std::string &s);
};

#endif // LEXER_HPP