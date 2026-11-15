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

double divi(double a, double b){
    if (b == 0.0){
        throw std::runtime_error("Division by zero");
    }
    return a/b;
}

double exponent( double a, double b){
    double result = 1;
    bool neg_flag = false;
    if (b == 0){
        return result;
    }
    else if (a == 0){
        return 0;
    }
    else {
        if (b<0) {
            neg_flag = true;
            b = -1*b;
        }
        for (int i=0; i<b; i++){
            result = result * a;
        }
        if (neg_flag == true){
            neg_flag = false;
            return divi(1,result);
        }
        return result;
    }
}
