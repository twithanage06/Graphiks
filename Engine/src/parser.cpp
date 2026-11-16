#include "parser.hpp"
#include "evaluator.hpp"


using namespace std;

Parser::Parser(const vector<Token>& tokens): tokens(tokens) {}

void Parser::expect(TokenType type, const string& error) {
    if (position >= tokens.size() || tokens[position].type != type) { 
        throw runtime_error(error);
    }

    position++;
}

double Parser::parsePrimary(){
    if (position >= tokens.size()){
        throw runtime_error("Position greater than token length");
    }

    const Token& current_val = tokens[position];

    if (current_val.type == TokenType::Root) {
        position++;

        expect(TokenType::LeftParam, "Expected '(' after root");

        double a = parseExpression();

        expect(TokenType::Comma, "Expected comma");

        double q = parseExpression();

        expect(TokenType::RightParam, "Expected ')' after root");

        //Check for 1. valid number 2. Integer 3. can fit in a C++ int
        if (!std::isfinite(q) || std::trunc(q) != q || q < std::numeric_limits<int>::min() || q > std::numeric_limits<int>::max()) {
            throw runtime_error("Invalid root degree");
        }

        return nthRoot(a, static_cast<int>(q));
    }

    if (current_val.type == TokenType::LeftParam) { //Parenthesiss
        position++;
        if (position < tokens.size() && tokens[position].type == TokenType::RightParam) {
            throw runtime_error("Empty parenthesis");
        }
        double result = parseExpression();
        if(position >= tokens.size() || tokens[position].type != TokenType::RightParam){
            throw runtime_error("No closing parenthesis");
        } 
        
        position++;
        return result;
    }
    else if (current_val.type == TokenType::Number){ //Detected a number (lowest in the hierarchy)
        double value = current_val.value;
        position++;
        return value;
    }
    throw runtime_error("Expected a number");
}


double Parser::parseExponent() {
    double left = parsePrimary();

    if (position < tokens.size() && tokens[position].type == TokenType::Exponent) {
        position++;

        double right = parseUnary();

        left = exponent(left, right);
    }

    return left;
}


double Parser::parseUnary() {
    if (position >= tokens.size()) {
        throw runtime_error("Expected a number");
    }

    if (tokens[position].type == TokenType::Subtract) {
        position++;
        return -parseUnary();
    }

    return parseExponent();
}


double Parser::parseTerm() {
    double left = parseUnary();

    while (position < tokens.size()) {
        TokenType op = tokens[position].type;

        if (op != TokenType::Multiply && op != TokenType::Divide) {
            break;
        }

        position++;

        double right = parseUnary();
        if (op == TokenType::Multiply){
            left = mult(left, right);
        }
        else if (op == TokenType::Divide) {
            left = divi(left, right);
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
    double result = parseExpression(); //Equate using recursion

    if (position != tokens.size()) {
        if (tokens[position].type == TokenType::RightParam) {
            throw runtime_error("Missing opening parenthesis");
        }
        throw runtime_error("Unexpected token");
    }

    return result;
}