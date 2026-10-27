#include "tokeniser.hpp"
#include <cstdio> 
#include <string>
#include <vector>

using namespace std;

vector<Token> tokenise(const string& expression){
    vector<Token> tokens;
    string current_num;
    char op;
    for (size_t i = 0; i < expression.length(); i++){
        char current_char = expression[i];
        bool operator_flag = false;
        switch (current_char){
            case '+':
                op = '+';
                operator_flag = true;
                break;
            case '-':
                op = '-';
                operator_flag = true;
                break;
            case '*':
                op = '*';
                operator_flag = true;
                break;
            case '/':
                op = '/';
                operator_flag = true;
                break;
            case '(':
                op = '(';
                operator_flag = true;
                break;
            case ')':
                op = ')';
                operator_flag = true;
                break;
        }
        if (current_char != ' ' && operator_flag == false){
            current_num = current_num + current_char;
        }
        else if (operator_flag) {

            if (!current_num.empty()) {
                tokens.push_back({TokenType::Number, stod(current_num)});
                current_num.clear();
            }

            switch (op) {
                case '+':
                    tokens.push_back({TokenType::Plus});
                    break;
                case '-':
                    tokens.push_back({TokenType::Subtract});
                    break;
                case '*':
                    tokens.push_back({TokenType::Multiply});
                    break;
                case '/':
                    tokens.push_back({TokenType::Divide});
                    break;
                case '(':
                    tokens.push_back({TokenType::LeftParam});
                    break;
                case ')':
                    tokens.push_back({TokenType::RightParam});
                    break;
            }
        }
    }
    if (current_num.length() > 0){
        tokens.push_back({TokenType::Number, stod(current_num)});
        current_num.clear();
    }
    return tokens;

}

