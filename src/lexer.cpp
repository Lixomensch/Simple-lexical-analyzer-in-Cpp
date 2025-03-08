#include "../include/lexer.hpp"
#include <cctype>
#include <unordered_set>
#include <algorithm>

const std::unordered_set<std::string> keywords = {"if", "else", "while", "int", "float"};
const std::unordered_set<std::string> operators = {"+", "-", "*", "/", "=", "!=", "<=", ">="};
const std::unordered_set<char> punctuation = {'(', ')', '{', '}', ';'};

Lexer::Lexer(const std::string &source) : source(source), index(0) {}

std::vector<Token> Lexer::tokenize()
{
    while (index < source.size())
    {
        processToken();
    }
    return tokens;
}

void Lexer::processToken()
{
    while (index < source.size() && std::isspace(source[index]))
    {
        ++index;
    }

    if (index >= source.size())
        return;

    std::string current;
    if (std::isalpha(source[index]))
    {
        while (index < source.size() && (std::isalnum(source[index]) || source[index] == '_'))
        {
            current += source[index++];
        }
        tokens.push_back({current, classifyToken(current)});
    }
    else if (std::isdigit(source[index]))
    {
        while (index < source.size() && (std::isdigit(source[index]) || source[index] == '.'))
        {
            current += source[index++];
        }
        tokens.push_back({current, classifyToken(current)});
    }
    else if (source[index] == '"')
    {
        current += source[index++];
        while (index < source.size() && source[index] != '"')
        {
            current += source[index++];
        }
        if (index < source.size())
            current += source[index++];
        tokens.push_back({current, TokenType::STRING});
    }
    else
    {
        std::string op(1, source[index]);
        if (index + 1 < source.size() && operators.count(op + source[index + 1]))
        {
            op += source[++index];
        }
        tokens.push_back({op, classifyToken(op)});
        ++index;
    }
}

TokenType Lexer::classifyToken(const std::string &token)
{
    if (keywords.count(token))
        return TokenType::KEYWORD;
    if (operators.count(token))
        return TokenType::OPERATOR;
    if (punctuation.count(token[0]))
        return TokenType::PUNCTUATION;
    if (isNumber(token))
        return TokenType::INTEGER;
    if (token.find('.') != std::string::npos)
        return TokenType::FLOAT;
    return TokenType::IDENTIFIER;
}

bool Lexer::isNumber(const std::string &s)
{
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
