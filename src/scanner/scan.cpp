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


std::pair<std::vector<std::string>, std::vector<std::string>> scan_file(const std::vector<std::string> &file_contents) {
    std::vector<std::string> tokens;
    std::vector<std::string> lexical_errors;

    for (int idx = 0; idx < file_contents.size(); idx++) {
        int line = idx + 1;
        const std::string &file_content = file_contents[idx];

        for (char ch: file_content) {
            TokenType token_type = identify_token(ch);

            const Token token = Token{ch, token_type, line};
            if (token_type == TokenType::UNKNOWN) {
                lexical_errors.push_back(token.to_lexical_error());
                continue;
            }
            tokens.push_back(token.to_string());
        }
    }

    // EOF file token
    tokens.push_back(Token{EOF, TokenType::END_OF_FILE, file_contents.size()}.to_string());
    return std::make_pair(tokens, lexical_errors);
}