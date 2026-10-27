#pragma once
#include <string>
#include <vector> 

using namespace std;

enum class TokenType{
    Number,
    Plus,
    Subtract,
    Multiply,
    Divide,
    LeftParam,
    RightParam,
    End
};

struct Token {
    TokenType type;
    double value = 0.0;
};

vector<Token> tokenise(const string& expression);