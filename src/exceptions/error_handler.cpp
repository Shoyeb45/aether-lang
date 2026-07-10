#include "error_handler.hpp"

#include <iostream>

void ErrorHandler::set_file_name(std::string file_name) {
    this->file_name = file_name;
}

void ErrorHandler::set_file_contents(std::vector<std::string> &file_contents) {
    this->file_contents = file_contents;
}

std::string ErrorHandler::format_err_message(Token &token, std::string &message) {
    std::string err_message = file_name + ":" + std::to_string(token.line) + ":" + std::to_string(token.column) + ": ";
    err_message += "\033[31mError\033[0m " + message + "\n";
    err_message += "    " + std::to_string(token.line) + " | " + file_contents[token.line - 1] + "\n";

    for (int i = 0; i < token.column + std::to_string(token.line).size() + 2 + 4; i++) {
        err_message += " ";
    }
    err_message += "\033[32m^\033[0m\n";
    return err_message;
}

void ErrorHandler::show_compile_error() {
    if (compiler_errors.size() == 0) {
        return;
    }

    for (auto &[token, message] : compiler_errors) {
        std::cerr << format_err_message(token, message);
    }
    std::exit(65);
}

void ErrorHandler::report_compile_error(std::string message, Token token) {
    compiler_errors.push_back(std::make_pair(token, message));
}

void ErrorHandler::report_runtime_error(std::string message, Token token) {
    std::cerr << format_err_message(token, message);
    std::exit(70);
}

void ErrorHandler::clear_errors() {
    compiler_errors.clear();
}
