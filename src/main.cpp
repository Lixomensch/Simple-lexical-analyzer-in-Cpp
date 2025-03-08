#include "../include/lexer.hpp"
#include <fstream>

void printTokens(const vector<Token> &tokens)
{
    for (const auto &token : tokens)
    {
        cout << "(" << token.value << ", ";
        switch (token.type)
        {
        case TokenType::KEYWORD:
            cout << "palavra-chave)";
            break;
        case TokenType::IDENTIFIER:
            cout << "identificador)";
            break;
        case TokenType::OPERATOR:
            cout << "operador)";
            break;
        case TokenType::PUNCTUATION:
            cout << "pontuação)";
            break;
        case TokenType::INTEGER:
            cout << "literal inteiro)";
            break;
        case TokenType::FLOAT:
            cout << "literal float)";
            break;
        case TokenType::STRING:
            cout << "string)";
            break;
        }
        cout << endl;
    }
}

string readFile(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Uso: " << argv[0] << " <arquivo de código-fonte>" << endl;
        return 1;
    }

    string code = readFile(argv[1]);
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    return 0;
}
