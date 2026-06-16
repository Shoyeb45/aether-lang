#pragma once

#include <string>

enum class TokenType {
    END_OF_FILE,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::string literal;

    // int line;
    // int column;

    std::string to_string() const;
    std::string token_type_to_string() const;
};