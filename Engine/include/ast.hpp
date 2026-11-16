#pragma once

#include <memory>

enum class NodeType{
    Number,
    Add,
    Subtract,
    Multiply,
    Divide,
    Exponent,
    Root,
    Negate
};

struct Node{
    NodeType type;
    double value = 0.0;

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};