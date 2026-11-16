#include "evaluator.hpp"
#include <ostream>
#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>

double absolute(double a){
    if (a < 0){
        return -a;
    }
    return a;
}

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


double exponent (double x, double n) {
    //Fractional exponents (e.g 2^0.5) aren't built yet
    if (!std::isfinite(n) || std::trunc(n) != n) {
        throw std::runtime_error("Fractional exponent unsupported");
    }
    double temp_x;
    if (n == 0) {
        return 1;
    }
    //Negative exponents
    if (n < 0) {
        if (x == 0) {
            throw std::runtime_error("Division by zero");
        }

        return 1.0 / exponent(x, -n);
    }
    //(x^n)^2 i.e ven exponents
    if (std::fmod(n, 2.0) == 0) {
        temp_x = exponent(x, n / 2);
        return temp_x * temp_x;
    }
    if (n == 1) {
        return x;
    }
    //x^n = x*(x^((n-1)/2))^2 i.e odd exponents
    temp_x = exponent(x, (n - 1) / 2);
    return x * temp_x * temp_x;
}

double nthRoot(double a, int q, double guess, int counter) {
    const double accuracy = 1e-10;
    double a_next = (1.0/q)*(((q-1)*guess)+(a/exponent(guess,(q-1))));

    if (absolute(a_next-guess) <= accuracy*absolute(a_next) || counter > 100){
        return a_next;
    }
    counter++;
    return nthRoot(a, q, a_next, counter);
}

double nthRoot(double a, int q) {
    double guess;
    if (q == 0) {
        throw std::runtime_error("Invalid root degree");
    }
    if (q < 0) {
        if (a == 0) {
            throw std::runtime_error("Division by zero");
        }

        return 1.0 / nthRoot(a, -q);
    }
    if (a==0){
        return 0;
    }
    if(a < 0 && q % 2 == 0){
        throw std::runtime_error("Even root of a negative number");
    }
    if (q==1){
        return a;
    }


    uint64_t bits;
    std::memcpy(&bits, &a, sizeof(a));
    uint64_t shifted_bit = bits >> 52;
    uint64_t stored_exponent = shifted_bit & 0x7FF;
    int e = static_cast<int>(stored_exponent) - 1023;

    guess = exponent(2.0,(e/q));
    if (a < 0) {
        guess = -guess;
    }
    
    return nthRoot(a, q, guess, 0);
}
