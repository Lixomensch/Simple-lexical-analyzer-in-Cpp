#include "../include/lexer.hpp"
#include <cctype>
#include <algorithm>

const unordered_set<string> keywords = {"if", "else", "while", "int", "float"};
const unordered_set<string> operators = {"+", "-", "*", "/", "=", "!=", "<=", ">="};
const unordered_set<char> punctuation = {'(', ')', '{', '}', ';'};

Lexer::Lexer(const string &source) : source(source), index(0) {}

vector<Token> Lexer::tokenize()
{
    while (index < source.size())
    {
        processToken();
    }
    return tokens;
}

void Lexer::processToken()
{
    while (index < source.size() && isspace(source[index]))
    {
        ++index;
    }

    if (index >= source.size())
        return;

    if (source[index] == '/' && index + 1 < source.size() && source[index + 1] == '/')
    {
        while (index < source.size() && source[index] != '\n')
        {
            ++index;
        }
        return;
    }

    string current;
    if (isalpha(source[index]))
    {
        while (index < source.size() && (isalnum(source[index]) || source[index] == '_'))
        {
            current += source[index++];
        }
        tokens.push_back({current, classifyToken(current)});
    }
    else if (isdigit(source[index]))
    {
        while (index < source.size() && (isdigit(source[index]) || source[index] == '.'))
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
        string op(1, source[index]);
        if (index + 1 < source.size() && operators.count(op + source[index + 1]))
        {
            op += source[++index];
        }
        tokens.push_back({op, classifyToken(op)});
        ++index;
    }
}

TokenType Lexer::classifyToken(const string &token)
{
    if (keywords.count(token))
        return TokenType::KEYWORD;
    if (operators.count(token))
        return TokenType::OPERATOR;
    if (punctuation.count(token[0]))
        return TokenType::PUNCTUATION;
    if (isNumber(token))
        return TokenType::INTEGER;
    if (token.find('.') != string::npos)
        return TokenType::FLOAT;
    return TokenType::IDENTIFIER;
}

bool Lexer::isNumber(const string &s)
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}
