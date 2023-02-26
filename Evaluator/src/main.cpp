#include <cstring>
#include <cmath>
#include <filesystem>
#include <fstream>

#include "lexer.hpp"
#include "parser.hpp"

struct Number {
    double value;
    bool is_float;

    Number() = default;
    Number(double value, const bool is_float) : value(value), is_float(is_float) {}
};

struct Interpreter {
    Number visit(Expression* node) {
        if (auto n = dynamic_cast<NumberExpression*>(node)) {
            return visit_number_node(n);
        } else if (auto n = dynamic_cast<UnaryOperationExpression*>(node)) {
            return visit_unary_operation_node(n);
        } else if (auto n = dynamic_cast<BinaryOperationExpression*>(node)) {
            return visit_binary_operation_node(n);
        }

        std::cerr << "Something went really wrong" << std::endl;
        return Number(0, false);
    }

    Number visit_number_node(NumberExpression* node) {
        return Number(std::atof(std::string(node->token.value).c_str()), node->token.type == FLOAT);
    }

    Number visit_unary_operation_node(UnaryOperationExpression* node) {
        auto number = visit(node->expression.get());

        if (node->op.type == BITWISE_NEGATION) {
            if (number.is_float) {
                std::cerr << "Cannot have a float in bitwise negation";
                return Number(0, false);
            }
            return Number(~static_cast<std::int64_t>(number.value), false);
        }
        if (node->op.type == PLUS) return Number(number.value, number.is_float);
        if (node->op.type == MINUS) return Number(-number.value, number.is_float);
        if (node->op.type == NOT) return Number(!static_cast<int>(number.value), false);
        return Number(0, false);
    }

    Number visit_binary_operation_node(BinaryOperationExpression* node) {
        auto left = visit(node->left.get());
        auto right = visit(node->right.get());

        if (node->op.type == BITWISE_NEGATION) {
            std::cerr << "Bit negation cannot be used as a binary operator" << std::endl;
            return Number(0, false);
        }
        if (node->op.type == PLUS) {
            if (left.is_float || right.is_float) return Number(left.value + right.value, true);
            return Number(static_cast<std::int64_t>(left.value) + static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == MINUS) {
            if (left.is_float || right.is_float) return Number(left.value - right.value, true);
            return Number(static_cast<std::int64_t>(left.value) - static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == MUL) {
            if (left.is_float || right.is_float) return Number(left.value * right.value, true);
            return Number(static_cast<std::int64_t>(left.value) * static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == DIV) {
            if (left.is_float || right.is_float) return Number(left.value / right.value, true);
            if (right.value == 0) {
                std::cerr << "Cannot divide integer by zero" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) / static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == MOD) {
            if (left.is_float || right.is_float) {
                std::cerr << "Cannot have a float in modulo operation" << std::endl;
                return Number(0, false);
            }
            if (right.value == 0) {
                std::cerr << "Cannot modulo by zero" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) % static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == BITWISE_LEFT) {
            if (left.is_float || right.is_float) {
                std::cerr << "Cannot have a float in bitwise-left operation" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) << static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == BITWISE_RIGHT) {
            if (left.is_float || right.is_float) {
                std::cerr << "Cannot have a float in bitwise-right operation" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) >> static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == POW) {
            return Number(std::pow(left.value, right.value), true);
        }
        if (node->op.type == EQUALS) {
            return Number(left.value == right.value, false);
        }
        if (node->op.type == NOT_EQUALS) {
            return Number(left.value != right.value, false);
        }
        if (node->op.type == LESS_THAN) {
            return Number(left.value < right.value, false);
        }  
        if (node->op.type == GREATER_THAN) {
            return Number(left.value > right.value, false);
        }
        if (node->op.type == LESS_THAN_OR_EQUALS) {
            return Number(left.value <= right.value, false);
        }
        if (node->op.type == GREATER_THAN_OR_EQUALS) {
            return Number(left.value >= right.value, false);
        }
        if (node->op.type == AND) {
            return Number(left.value && right.value, false);
        }
        if (node->op.type == OR) {
            return Number(left.value || right.value, false);
        }
        if (node->op.type == BITWISE_AND) {
            if (left.is_float || right.is_float) {
                std::cerr << "Cannot have a float in bitwise-and" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) & static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == BITWISE_OR) {
            if (left.is_float || right.is_float) {
                std::cerr << "Cannot have a float in bitwise-or" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) | static_cast<std::int64_t>(right.value), false);
        }
        if (node->op.type == BITWISE_XOR) {
            if (left.is_float || right.is_float) {
                std::cerr << "Cannot have a float in bitwise-xor" << std::endl;
                return Number(0, false);
            }
            return Number(static_cast<std::int64_t>(left.value) ^ static_cast<std::int64_t>(right.value), false);
        }

        std::cerr << "Something went really wrong with binary operation" << std::endl;
        return Number(0, false);
    }

    Interpreter() = default;
};

static double execute(std::string* code) {
    Lexer lexer(code);
    auto tokens = lexer.make_tokens();
    Parser parser(tokens);
    auto ast = parser.parse();

    if (!ast) return 0;

    Interpreter interpreter;
    auto result = interpreter.visit(ast.get());

    return result.value;
}


int main(int argc, char** argv) {
    std::cout << "Enter an expression\n >>> ";
    std::string text;
    std::getline(std::cin, text);
    std::cout << "Parsing the expression \"" << text << "\"..." << std::endl;
    auto result = execute(&text);

    std::cout << result << std::endl;

    return 0;
}