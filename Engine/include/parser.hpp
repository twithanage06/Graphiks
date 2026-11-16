#pragma once

#include "tokeniser.hpp"
#include "ast.hpp"
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <string>
#include <memory>


class Parser {
private:
    const std::vector<Token>& tokens;
    std::size_t position = 0;
    void expect(TokenType type, const std::string& error);
    std::unique_ptr<Node> parseExpression();
    std::unique_ptr<Node> parseTerm();
    std::unique_ptr<Node> parseUnary();
    std::unique_ptr<Node> parseExponent();
    std::unique_ptr<Node> parsePrimary();

public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Node> parse();
};