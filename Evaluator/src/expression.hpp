#pragma once

#include <iostream>
#include <memory>

#include "token.hpp"

static std::string make_tabs(const std::size_t scope);

struct Expression {
    virtual std::string stringify(std::size_t& scope) const;

    virtual ~Expression() {}
};

struct NumberExpression : public Expression {
    Token token;

    std::string stringify(std::size_t& scope) const override;

    NumberExpression() = default;
    NumberExpression(const Token& token) : token(token) {}
};

struct BinaryOperationExpression : public Expression {
    std::unique_ptr<Expression> left;
    Token op;
    std::unique_ptr<Expression> right;

    std::string stringify(std::size_t& scope) const override;

    BinaryOperationExpression() = default;
    BinaryOperationExpression(std::unique_ptr<Expression> left, const Token& op, std::unique_ptr<Expression> right) : left(std::move(left)), op(op), right(std::move(right)) {}
};

struct UnaryOperationExpression: public Expression {
    Token op;
    std::unique_ptr<Expression> expression;

    std::string stringify(std::size_t& scope) const override;

    UnaryOperationExpression() = default;
    UnaryOperationExpression(const Token& op, std::unique_ptr<Expression> expression) : op(op), expression(std::move(expression)) {}
};