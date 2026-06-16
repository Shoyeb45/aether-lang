#include "scanner.hpp"
#include "token.hpp"

std::vector<std::string> scan_file(const std::string &file_content) {
    std::vector<std::string> tokens;

    for (int idx = 0; idx < file_content.size(); idx++) {
        switch (file_content[idx]) {
        case '(':
            tokens.push_back(Token{TokenType::LEFT_PAREN, "(", "null"}.to_string());
            break;
        case ')':
            tokens.push_back(Token{TokenType::RIGHT_PAREN, ")", "null"}.to_string());
            break;
        case '{':
            tokens.push_back(Token{TokenType::LEFT_BRACE, "{", "null"}.to_string());
            break;
        case '}':
            tokens.push_back(Token{TokenType::RIGHT_BRACE, "}", "null"}.to_string());
            break;
        }
    }

    // EOF file token
    tokens.push_back(Token{TokenType::END_OF_FILE, "", "null"}.to_string());
    return tokens;
}