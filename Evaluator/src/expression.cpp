#include "expression.hpp"

void Expression::print(const std::string& prefix, const bool isLeft) const {
    std::cout << "Error: This expression is the base class and there should not be any instance of this type." << std::endl;
}

void NumberExpression::print(const std::string& prefix, const bool isLeft) const {
    std::cout << prefix + (isLeft ? "├──" : "└──" ) << token.value << std::endl;
}

void BinaryOperationExpression::print(const std::string& prefix, const bool isLeft) const {
    std::cout << prefix + (isLeft ? "├──" : "└──" ) << stringify_token_type(op.type) << std::endl;
    left->print(prefix + (isLeft ? "│   " : "    "), true);
    right->print(prefix + (isLeft ? "│   " : "    "), false);
}

void UnaryOperationExpression::print(const std::string& prefix, const bool isLeft) const {
    std::cout << prefix + (isLeft ? "├──" : "└──" ) << stringify_token_type(op.type) << std::endl;
    expression->print(prefix + (isLeft ? "│   " : "    "), false);
}