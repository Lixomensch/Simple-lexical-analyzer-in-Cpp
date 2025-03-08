#include "../include/lexer.hpp"
#include <fstream>

void printTokens(const std::vector<Token> &tokens)
{
    for (const auto &token : tokens)
    {
        std::cout << "(" << token.value << ", ";
        switch (token.type)
        {
        case TokenType::KEYWORD:
            std::cout << "palavra-chave)";
            break;
        case TokenType::IDENTIFIER:
            std::cout << "identificador)";
            break;
        case TokenType::OPERATOR:
            std::cout << "operador)";
            break;
        case TokenType::PUNCTUATION:
            std::cout << "pontuação)";
            break;
        case TokenType::INTEGER:
            std::cout << "literal inteiro)";
            break;
        case TokenType::FLOAT:
            std::cout << "literal float)";
            break;
        case TokenType::STRING:
            std::cout << "string)";
            break;
        }
        std::cout << std::endl;
    }
}

std::string readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        exit(1);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <arquivo de código-fonte>" << std::endl;
        return 1;
    }

    std::string code = readFile(argv[1]);
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    return 0;
}
