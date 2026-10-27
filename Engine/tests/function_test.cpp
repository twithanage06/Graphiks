#include "../include/tokeniser.hpp"
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct TestCase {
    string name;
    string expression;
    vector<Token> expected;
};

void token_test(){

    vector<TestCase> tests = {
        {
            "Basic Addition",
            "1 + 2",
            {
                {TokenType::Number, 1},
                {TokenType::Plus},
                {TokenType::Number, 2}
            }
        },
        {
            "Negative Number",
            "-5 + 4",
            {
                {TokenType::Subtract},
                {TokenType::Number, 5},
                {TokenType::Plus},
                {TokenType::Number, 4}
            }
        },
        {
            "Parentheses",
            "(3 + 2)",
            {
                {TokenType::LeftParam},
                {TokenType::Number, 3},
                {TokenType::Plus},
                {TokenType::Number, 2},
                {TokenType::RightParam}
            }

        },
        {
            "Decimals",
            "(3.14 * 2.72)",
            {
                {TokenType::LeftParam},
                {TokenType::Number, 3.14},
                {TokenType::Multiply},
                {TokenType::Number, 2.72},
                {TokenType::RightParam}
            }

        }
    };
    int passed = 0;
    int failed = 0;

    for (const TestCase& test : tests) {
        vector<Token> actual = tokenise(test.expression);

        bool success = actual.size() == test.expected.size();

        if (success) {
            for (size_t i = 0; i < actual.size(); i++) {
                if (actual[i].type != test.expected[i].type ||
                    actual[i].value != test.expected[i].value) {
                    success = false;
                    break;
                }
            }
        }

        if (success) {
            printf("[PASS] %s\n", test.name.c_str());
            passed++;
        } else {
            printf("[FAIL] %s\n", test.name.c_str());
            failed++;
        }
    }

    printf("\nResults: %d passed, %d failed\n", passed, failed);
}

int main() {
    token_test();

    return 0;
}