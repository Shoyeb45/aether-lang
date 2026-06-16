#include "token.hpp"

std::string Token::to_string() const {
    std::string lexeme = this->lexeme;
    if (lexeme == "") {
        lexeme = this->token_type_to_symbol();
    }
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
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::DOT:
            return "DOT";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::SLASH:
            return "SLASH";
        case TokenType::STAR:
            return "STAR";
        default:
            return "";
    }
}

std::string Token::token_type_to_symbol() const {
    switch (type) {
        case TokenType::END_OF_FILE:
            return "";
        case TokenType::LEFT_PAREN:
            return "(";
        case TokenType::RIGHT_PAREN:
            return ")";
        case TokenType::LEFT_BRACE:
            return "{";
        case TokenType::RIGHT_BRACE:
            return "}";
        case TokenType::COMMA:
            return ",";
        case TokenType::DOT:
            return ".";
        case TokenType::MINUS:
            return "-";
        case TokenType::PLUS:
            return "+";
        case TokenType::SEMICOLON:
            return ";";
        case TokenType::SLASH:
            return "/";
        case TokenType::STAR:
            return "*";
        default:
            return "";
    }
}