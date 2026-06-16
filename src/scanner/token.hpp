#pragma once

#include <string>

enum class TokenType {
    END_OF_FILE,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::string literal;
    char original_token;
    int line;
    // int column;

    Token(char, TokenType, int);
    Token(char, TokenType, std::string, std::string, int);

    std::string to_string() const;
    std::string token_type_to_string() const;
    std::string token_type_to_symbol() const;
    std::string to_lexical_error() const;
};