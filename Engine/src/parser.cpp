#include "parser.hpp"
#include "evaluator.hpp"
#include <stdexcept>
#include <vector>
#include <cstddef>

using namespace std;

Parser::Parser(const vector<Token>& tokens): tokens(tokens) {}

double Parser::parseFactor(){
    if (position >= tokens.size()){
        throw runtime_error("Position greater than token length");
    }

    const Token& current_val = tokens[position];
    if (current_val.type == TokenType::Subtract) {
    position++;
    return -parseFactor();
    }
    
    if (current_val.type == TokenType::Number){
        double value = current_val.value;
        position++;
        return value;
    }

    throw runtime_error("Expected a number");
}

double Parser::parseTerm() {
    double left = parseFactor();

    while (position < tokens.size()) {
        TokenType op = tokens[position].type;

        if (op != TokenType::Multiply && op != TokenType::Divide) {
            break;
        }

        position++;

        double right = parseFactor();
        if (op == TokenType::Multiply){
            left = mult(left, right);
        }
        else if (op == TokenType::Divide) {
            left = div(left, right);
        }

    }

    return left;
}

double Parser::parseExpression() {
    double left = parseTerm();

    while (position < tokens.size()) {
        TokenType op = tokens[position].type;

        if (op != TokenType::Plus && op != TokenType::Subtract) {
            break;
        }
        position++;

        double right = parseTerm();
        if (op == TokenType::Plus){
            left = add(left, right);
        }
        else if (op == TokenType::Subtract) {
            left = sub(left, right);
        }

    }

    return left;
}

double Parser::parse() {
    double result = parseExpression();

    if (position != tokens.size()) {
        throw runtime_error("Unexpected token");
    }

    return result;
}