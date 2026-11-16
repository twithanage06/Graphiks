#pragma once

#include "tokeniser.hpp"
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <string>

class Parser {
private:
    const std::vector<Token>& tokens;
    std::size_t position = 0;
    void expect(TokenType type, const string& error);
    double parseExpression();
    double parseTerm();
    double parseUnary();
    double parseExponent();
    double parsePrimary();
    
    

public:
    explicit Parser(const std::vector<Token>& tokens);
    double parse();
};