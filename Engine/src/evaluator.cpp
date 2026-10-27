#include "evaluator.hpp"
#include <stdexcept>
double add(double a, double b){
    return a+b;
}
double sub(double a, double b){
    return a-b;
}
double mult(double a, double b){
    return a*b;
}
double div(double a, double b){
    if (b == 0.0){
        throw std::domain_error("Division by zero");
    }
    return a/b;
}