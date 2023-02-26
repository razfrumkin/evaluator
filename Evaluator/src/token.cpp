#include "token.hpp"

std::string Token::stringify() const {
    return stringify_token_type(type) + ": " + std::string(value);
}

std::string stringify_token_type(const TokenType type) {
    switch (type) {
        case INT: return "Integer";
        case FLOAT: return "Float";
        case IDENTIFIER: return "Identifier";
        case AND: return "And";
        case OR: return "Or";
        case BITWISE_AND: return "Bitwise And";
        case BITWISE_OR: return "Bitwise Or";
        case BITWISE_XOR: return "Bitwise Xor";
        case NOT: return "Not";
        case BITWISE_NEGATION: return "Bitwise Negation";
        case PLUS: return "Plus";
        case MINUS: return "Minus";
        case MUL: return "Multiply";
        case DIV: return "Divide";
        case MOD: return "Modulo";
        case BITWISE_LEFT: return "Bitwise Left";
        case BITWISE_RIGHT: return "Bitwise Right";
        case POW: return "Power";
        case LPAREN: return "Left Parenthesis";
        case RPAREN: return "Right Parenthesis";
        case EQUALS: return "Equals";
        case NOT_EQUALS: return "Not Equals";
        case LESS_THAN: return "Less Than";
        case GREATER_THAN: return "Greater Than";
        case LESS_THAN_OR_EQUALS: return "Less Than Or Equals";
        case GREATER_THAN_OR_EQUALS: return "Greater Than Or Equals";
        case END_OF_FILE: return "End Of File";
        default: return "ERROR TYPE";
    }
}