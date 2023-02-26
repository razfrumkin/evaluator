#include "expression.hpp"

#define SPACE "  "

static std::string make_tabs(const std::size_t scope) {
    std::string result = "\n";
    for (std::size_t index = 0; index < scope; index += 1) result += SPACE;
    return result;
}

std::string Expression::stringify(std::size_t& scope) const {
    return "ERROR: THIS EXPRESSION IS THE BASE CLASS";
}

std::string NumberExpression::stringify(std::size_t& scope) const {
    scope += 1;
    std::string result = "";
    result += SPACE + std::string(token.value);
    scope -= 1;
    return result;
}

std::string BinaryOperationExpression::stringify(std::size_t& scope) const {
    scope += 1;
    std::string result = "";
    result += SPACE + stringify_token_type(op.type) + ':';
    result += make_tabs(scope) + left->stringify(scope);
    result += make_tabs(scope) + right->stringify(scope);;
    scope -= 1;
    return result;
}

std::string UnaryOperationExpression::stringify(std::size_t& scope) const {
    scope += 1;
    std::string result = "";
    result += SPACE + stringify_token_type(op.type);;
    result += make_tabs(scope) + expression->stringify(scope);
    scope -= 1;
    return result;
}