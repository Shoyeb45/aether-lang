#include "error_handler.hpp"

#include <iostream>

void ErrorHandler::set_file_name(std::string file_name) {
    this->file_name = file_name;
}

void ErrorHandler::set_file_contents(std::vector<std::string> &file_contents) {
    this->file_contents = file_contents;
}


void ErrorHandler::show_compile_error() {
    if (compiler_errors.size() == 0) {
        return;
    }

    for (auto &[token, message] : compiler_errors) {
        std::cerr << file_name << ":" << token.line << ":" << token.column << ": " << "\033[31mError\033[0m " << message
                  << "\n";
        std::cerr << "    " << token.line << " | " << file_contents[token.line - 1] << "\n";
        std::string white_space = "    ";
        for (int i = 0; i < token.column + std::to_string(token.line).size() + 2; i++) {
            white_space += " ";
        }
        std::cerr << white_space  << "\033[32m^" << "\n";
    }
    std::exit(65);
}

void ErrorHandler::report_compile_error(std::string message, Token token) {
    compiler_errors.push_back(std::make_pair(token, message));
}
