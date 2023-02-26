#include "parser.hpp"

Token Parser::advance() {
    index += 1;
    if (index < tokens.size()) current = tokens[index];
    return current;
}

std::unique_ptr<Expression> Parser::atom() {
    Token token = current;

    if (token.type == INT || token.type == FLOAT) {
        advance();
        return std::make_unique<NumberExpression>(token);
    } else if (token.type == LPAREN) {
        advance();
        auto value = expression();

        if (!value) {
            std::cout << "Invalid expression" << std::endl;
            return nullptr;
        }

        if (current.type == RPAREN) {
            advance();
            return std::move(value);
        }
        std::cerr << "Expected ')'" << std::endl;
        return nullptr;
    }

    std::cout << "Invalid unary operator" << std::endl;
    return nullptr;
}

std::unique_ptr<Expression> Parser::power() {
    return std::move(binary_operation(&Parser::atom, { POW }));
}

std::unique_ptr<Expression> Parser::factor() {
    Token token = current;

    if (token.type == BITWISE_NEGATION || token.type == PLUS || token.type == MINUS) {
        advance();
        auto value = factor();
        if (value) return std::make_unique<UnaryOperationExpression>(token, std::move(value));
        return nullptr;
    }

    return std::move(power());
}

std::unique_ptr<Expression> Parser::term() {
    return std::move(binary_operation(&Parser::factor, { MUL, DIV, MOD }));
}

std::unique_ptr<Expression> Parser::arithmetic() {
    return binary_operation(&Parser::term, { PLUS, MINUS, BITWISE_NEGATION });
}

std::unique_ptr<Expression> Parser::bitwise() {
    return binary_operation(&Parser::arithmetic, { BITWISE_LEFT, BITWISE_RIGHT });
}

std::unique_ptr<Expression> Parser::comparison() {
    if (current.type == NOT) {
        Token op = current;
        advance();

        auto node = comparison();
        if (node) return std::make_unique<UnaryOperationExpression>(op, std::move(node));
        return nullptr;
    }

    return binary_operation(&Parser::bitwise, { EQUALS, NOT_EQUALS, LESS_THAN, GREATER_THAN, LESS_THAN_OR_EQUALS, GREATER_THAN_OR_EQUALS });
}

std::unique_ptr<Expression> Parser::expression() {
    return std::move(binary_operation(&Parser::comparison, { AND, OR, BITWISE_AND, BITWISE_OR, BITWISE_XOR }));
}

std::unique_ptr<Expression> Parser::binary_operation(std::unique_ptr<Expression> (Parser::*first_function)(), const std::vector<TokenType>& operators, std::unique_ptr<Expression> (Parser::*second_function)()) {
    if (!second_function) second_function = first_function;

    auto left = (this->*first_function)();

    if (!left) return nullptr;

    while (exists_in(current.type, operators)) {
        Token op = current;
        advance();
        auto right = (this->*second_function)();
        if (!right) return nullptr;
        left = std::make_unique<BinaryOperationExpression>(std::move(left), op, std::move(right));
    }

    return left;
}

bool Parser::exists_in(const TokenType type, const std::vector<TokenType>& types) const {
    for (std::size_t type_index = 0; type_index < types.size(); type_index += 1) if (type == types[type_index]) return true;
    return false;
}

std::unique_ptr<Expression> Parser::parse() {
    return expression();
}