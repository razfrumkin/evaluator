#pragma once

#include <iostream>
#include <vector>

#include "token.hpp"
#include "expression.hpp"

class Parser {
    private:
    std::vector<Token> tokens;
    std::size_t index;
    Token current;

    Token advance();

    std::unique_ptr<Expression> atom();
    std::unique_ptr<Expression> power();
    std::unique_ptr<Expression> factor();
    std::unique_ptr<Expression> term();
    std::unique_ptr<Expression> arithmetic();
    std::unique_ptr<Expression> bitwise();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> binary_operation(std::unique_ptr<Expression> (Parser::*first_function)(), const std::vector<TokenType>& operators, std::unique_ptr<Expression> (Parser::*second_function)() = nullptr);

    bool exists_in(const TokenType type, const std::vector<TokenType>& types) const;

    public:
    std::unique_ptr<Expression> parse();

    Parser() = default;
    Parser(const std::vector<Token>& tokens) : tokens(tokens), index(-1) {
        advance();
    }
};