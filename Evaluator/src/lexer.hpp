#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <cctype>

#include "token.hpp"

class Lexer {
    private:
    std::string* code;
    std::size_t position;
    char current;

    void advance();

    Token make_number();
    Token make_identifier();
    Token make_equals();
    Token make_not_equals();
    Token make_less_than_or_bitwise_left();
    Token make_greater_than_or_bitwise_right();
    public:
    std::vector<Token> make_tokens();

    Lexer() = default;
    Lexer(std::string* code) : code(code), position(0), current((*code)[position]) {}
};