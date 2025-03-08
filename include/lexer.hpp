#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

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
    string value;
    TokenType type;
};

class Lexer
{
public:
    Lexer(const string &source);
    vector<Token> tokenize();

private:
    string source;
    size_t index;
    vector<Token> tokens;

    void processToken();
    TokenType classifyToken(const string &token);
    bool isNumber(const string &s);
};

#endif // LEXER_HPP