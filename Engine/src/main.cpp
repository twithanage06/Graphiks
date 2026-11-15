#include <iostream>
#include <vector>
#include "parser.hpp"

using namespace std;


int main() {
    string equation;
    cout << "Equation: " << endl;
    cin >> equation;

    vector<Token> tokens = tokenise(equation);
    try {
        Parser parser(tokens);
        double result = parser.parse();
        printf("Result: %g\n", result);
    }
    catch (const std::exception& e){
        cerr << "Error: " << e.what() << endl;
    }



    return 0;
}