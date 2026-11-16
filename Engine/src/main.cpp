#include <iostream>
#include <vector>
#include "parser.hpp"

using namespace std;


int main() {
    
    string equation;;
    getline(cin,equation);

    try {
        vector<Token> tokens = tokenise(equation);
        Parser parser(tokens);
        double result = parser.parse();
        cout << result << endl;
    }
    catch (const std::exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }



    return 0;
}