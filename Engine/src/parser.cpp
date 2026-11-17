#include "parser.hpp"
#include "evaluator.hpp"
#include "ast.hpp"

#include <memory>
#include <type_traits>

using namespace std;

Parser::Parser(const vector<Token>& tokens): tokens(tokens) {}

void Parser::expect(TokenType type, const string& error) {
    if (position >= tokens.size() || tokens[position].type != type) { 
        throw runtime_error(error);
    }

    position++;
}

unique_ptr<Node> Parser::parsePrimary(){
    if (position >= tokens.size()){ //To protect against an invalid positions
        throw runtime_error("Position greater than token length");
    }

    const Token& current_val = tokens[position];
    if (current_val.type == TokenType::Root){ //roots

        auto root = make_unique<Node>(); //Make root node
        root->type = NodeType::Root;

        position++;
        expect(TokenType::LeftParam, "Expected '(' after root");

        root->left = parseExpression(); //Make left side expression

        expect(TokenType::Comma, "Expected comma");

        root->right = parseExpression(); //Make right side expression

        expect(TokenType::RightParam, "Expected ')' after root");

        return root; //return this branch
    }
    if (current_val.type == TokenType::LeftParam){ //parenthesis
        position++;
        if (position < tokens.size() && tokens[position].type == TokenType::RightParam) { //empty parenthesis
            throw runtime_error("Empty parenthesis");
        }
        auto result = parseExpression(); //Make the expression within the parenthesis
        expect(TokenType::RightParam, "Expected ')'");
        return result; //return this branch
    }
    if (current_val.type == TokenType::Number){ //Numbers
        auto number = make_unique<Node>();
        number->type = NodeType::Number;
        number->value = current_val.value;
        position++;
        return number; //return this leaf
    }
    throw runtime_error("Expected a number or expression");
}


unique_ptr<Node> Parser::parseExponent() {
    auto left = parsePrimary();

    if (position < tokens.size() && tokens[position].type == TokenType::Exponent) {
        position++;

        auto right = parseUnary();
        
        auto root = make_unique<Node>();
        root->type = NodeType::Exponent;
        root->left = move(left);
        root->right = move(right);

        return root;
    }
    return left;
}


unique_ptr<Node> Parser::parseUnary() {
    if (position >= tokens.size()) {
        throw runtime_error("Expected a number");
    }

    if (tokens[position].type == TokenType::Subtract) {
        position++;
        auto root = make_unique<Node>();
        root->type = NodeType::Negate;

        root->left = parseUnary();

        return root;
    }

    return parseExponent();
}

unique_ptr<Node> Parser::parseTerm(){
    auto left = parseUnary();
    while (position < tokens.size()) {
        TokenType op = tokens[position].type;
        if (op != TokenType::Multiply && op != TokenType::Divide) {
            break;
        }
        position++;

        auto right = parseUnary();
        auto root = make_unique<Node>();
        if (op == TokenType::Divide){
            root->type = NodeType::Divide;
        }
        else if (op == TokenType::Multiply) {
            root->type = NodeType::Multiply;
        }
        root->left = move(left);
        root->right = move(right);

        left = move(root);
    }

    return left;
}

unique_ptr<Node> Parser::parseExpression(){
    auto left = parseTerm();

    while (position < tokens.size()) {
        TokenType op = tokens[position].type;
        if (op != TokenType::Plus && op != TokenType::Subtract) {
            break;
        }
        position++;

        auto right = parseTerm();
        auto root = make_unique<Node>();
        if (op == TokenType::Plus){
            root->type = NodeType::Add;
        }
        else if (op == TokenType::Subtract) {
            root->type = NodeType::Subtract;
        }
        root->left = move(left);
        root->right = move(right);

        left = move(root);
    }

    return left;

}

unique_ptr<Node> Parser::parse() {
    auto result = parseExpression();

    if (position != tokens.size()) {
        if (tokens[position].type == TokenType::RightParam) {
            throw runtime_error("Expected '('");
        }

        throw runtime_error("Unexpected token");
    }

    return result;
}
