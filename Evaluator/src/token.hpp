#pragma once

#include <string>
#include <string_view>

enum TokenType {
    INT,
    FLOAT,
    IDENTIFIER,

    AND,
    OR,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR,

    NOT,

    BITWISE_NEGATION,
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    BITWISE_LEFT,
    BITWISE_RIGHT,
    POW,
    LPAREN,
    RPAREN,
    EQUALS,
    NOT_EQUALS,
    LESS_THAN,
    GREATER_THAN,
    LESS_THAN_OR_EQUALS,
    GREATER_THAN_OR_EQUALS,

    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string_view value;

    std::string stringify() const;

    Token() = default;
    Token(const TokenType type) : type(type) {}
    Token(const TokenType type, const std::string_view& value) : type(type), value(value) {}
};

std::string stringify_token_type(const TokenType type);