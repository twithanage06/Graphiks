#include <iostream>
#include <vector>
#include "parser.hpp"
#include "evaluator.hpp"

using namespace std;


int main() {
    
    string equation;
    getline(cin,equation);

    try {
        vector<Token> tokens = tokenise(equation);
        Parser parser(tokens);
        auto tree = parser.parse();
        double result = evaluator(*tree);
        cout << result << '\n';
    }
    catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }



    return 0;
}