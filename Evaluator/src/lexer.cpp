#include "lexer.hpp"

void Lexer::advance() {
    position += 1;
    if (position < code->size()) current = (*code)[position];
}

Token Lexer::make_number() {
    const char* const start = code->c_str() + position;
    std::size_t dot_count = 0;

    while (position < code->size() && (current == '.' || std::isdigit(current))) {
        if (current == '.') {
            if (dot_count == 1) break;
            dot_count += 1;
        }
        advance();
    }

    if (dot_count == 0) return Token(INT, std::string_view(start, code->c_str() + position - start));
    else return Token(FLOAT, std::string_view(start, code->c_str() + position - start));
}

Token Lexer::make_identifier() {
    const char* const start = code->c_str() + position;
    
    while (position < code->size() && (current == '_' || std::isalnum(current))) {
        advance();
    }

    std::string_view value(start, code->c_str() + position - start);
    if (value == "and") return Token(AND);
    if (value == "band") return Token(BITWISE_AND);
    if (value == "bor") return Token(BITWISE_OR);
    if (value == "xor") return Token(BITWISE_XOR);
    if (value == "or") return Token(OR);
    if (value == "not") return Token(NOT);
    return Token(IDENTIFIER, value);
}

Token Lexer::make_not_equals() {
    const char* const start = code->c_str() + position;
    advance();

    if (current == '=') {
        advance();
        return Token(NOT_EQUALS, std::string_view(start, code->c_str() + position - start));
    }

    return Token(NOT_EQUALS, std::string_view(0, 0));
}

Token Lexer::make_less_than_or_bitwise_left() {
    TokenType type = LESS_THAN;
    const char* const start = code->c_str() + position;
    advance();

    if (current == '=') {
        advance();
        type = LESS_THAN_OR_EQUALS;
    } else if (current == '<') {
        advance();
        type = BITWISE_LEFT;
    }

    return Token(type, std::string_view(start, code->c_str() + position - start));
}

Token Lexer::make_greater_than_or_bitwise_right() {
    TokenType type = GREATER_THAN;
    const char* const start = code->c_str() + position;
    advance();

    if (current == '=') {
        advance();
        type = GREATER_THAN_OR_EQUALS;
    } else if (current == '>') {
        advance();
        type = BITWISE_RIGHT;
    }

    return Token(type, std::string_view(start, code->c_str() + position - start));
}

std::vector<Token> Lexer::make_tokens() {
    std::vector<Token> tokens;

    while (position < code->size()) {
        if (std::isspace(current)) advance();
        else if (std::isdigit(current)) {
            tokens.push_back(make_number());
        } else if (current == '_' || std::isalpha(current)) {
            tokens.push_back(make_identifier());
        } else if (current == '~') {
            tokens.push_back(Token(BITWISE_NEGATION));
            advance();
        } else if (current == '+') {
            tokens.push_back(Token(PLUS));
            advance();
        } else if (current == '-') {
            tokens.push_back(Token(MINUS));
            advance();
        } else if (current == '*') {
            tokens.push_back(Token(MUL));
            advance();
        } else if (current == '/') {
            tokens.push_back(Token(DIV));
            advance();
        } else if (current == '%') {
            tokens.push_back(Token(MOD));
            advance();
        } else if (current == '^') {
            tokens.push_back(Token(POW));
            advance();
        } else if (current == '(') {
            tokens.push_back(Token(LPAREN));
            advance();
        } else if (current == ')') {
            tokens.push_back(Token(RPAREN));
            advance();
        } else if (current == '!') {
            Token token = make_not_equals();
            if (!token.value.size()) return {};
            tokens.push_back(token);
        } else if (current == '<') {
            tokens.push_back(make_less_than_or_bitwise_left());
        } else if (current == '>') {
            tokens.push_back(make_greater_than_or_bitwise_right());
        } else {
            std::cerr << "Illegal character error: '" << current << '\'' << std::endl;
            advance();
            return {};
        }
    }

    tokens.push_back(Token(END_OF_FILE));
    return tokens;
}