#include "token.hpp"

std::string Token::to_string() const {
    return token_type_to_string() + " " + lexeme + " " + literal;
}

std::string Token::token_type_to_string() const {
    switch (type) {
        case TokenType::END_OF_FILE:
            return "EOF";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:
            return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:
            return "RIGHT_BRACE";
        default:
            return "";
    }
}