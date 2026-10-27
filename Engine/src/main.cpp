#include <iostream>
#include <vector>
#include "parser.hpp"

using namespace std;


int main() {
    string equation = "-5 + 3 * 4";

    vector<Token> tokens = tokenise(equation);

    Parser parser(tokens);

    double result = parser.parse();

    printf("Result: %g\n", result);
    return 0;
}