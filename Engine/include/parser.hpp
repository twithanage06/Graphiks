#pragma once

#include "tokeniser.hpp"
#include <vector>
#include <cstddef>

class Parser {
private:
    const std::vector<Token>& tokens;
    std::size_t position = 0;

    double parseExpression();
    double parseTerm();
    double parseFactor();

public:
    explicit Parser(const std::vector<Token>& tokens);
    double parse();
};