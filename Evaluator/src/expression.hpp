#pragma once

#include <iostream>
#include <memory>

#include "token.hpp"

struct Expression {
    virtual void print(const std::string& prefix, const bool isLeft) const;

    virtual ~Expression() {}
};

struct NumberExpression : public Expression {
    Token token;

    void print(const std::string& prefix, const bool isLeft) const override;

    NumberExpression() = default;
    NumberExpression(const Token& token) : token(token) {}
};

struct BinaryOperationExpression : public Expression {
    std::unique_ptr<Expression> left;
    Token op;
    std::unique_ptr<Expression> right;

    void print(const std::string& prefix, const bool isLeft) const override;

    BinaryOperationExpression() = default;
    BinaryOperationExpression(std::unique_ptr<Expression> left, const Token& op, std::unique_ptr<Expression> right) : left(std::move(left)), op(op), right(std::move(right)) {}
};

struct UnaryOperationExpression: public Expression {
    Token op;
    std::unique_ptr<Expression> expression;

    void print(const std::string& prefix, const bool isLeft) const override;

    UnaryOperationExpression() = default;
    UnaryOperationExpression(const Token& op, std::unique_ptr<Expression> expression) : op(op), expression(std::move(expression)) {}
};