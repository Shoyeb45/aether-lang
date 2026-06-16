#include "scanner.hpp"
#include "token.hpp"
#include <iostream>

TokenType identify_token(char ch) {
    switch (ch) {
    case '(':
        return TokenType::LEFT_PAREN;
    case ')':
        return TokenType::RIGHT_PAREN;
    case '{':
        return TokenType::LEFT_BRACE;
    case '}':
        return TokenType::RIGHT_BRACE;
    case ',':
        return TokenType::COMMA;
    case '.':
        return TokenType::DOT;
    case '-':
        return TokenType::MINUS;
    case '+':
        return TokenType::PLUS;
    case '*':
        return TokenType::STAR;
    case ';':
        return TokenType::SEMICOLON;
    case '/':
        return TokenType::SLASH;
    }
    return TokenType::UNKNOWN;
}

std::vector<std::string> scan_file(const std::string &file_content) {
    std::vector<std::string> tokens;

    for (int idx = 0; idx < file_content.size(); idx++) {
        TokenType token_type = identify_token(file_content[idx]);
        if (token_type == TokenType::UNKNOWN) {
            std::cerr << "Unknown token found: " << file_content[idx] << "\n";
            continue;
        }
        tokens.push_back(Token{token_type, "", "null"}.to_string());
    }

    // EOF file token
    tokens.push_back(Token{TokenType::END_OF_FILE, "", "null"}.to_string());
    return tokens;
}