#pragma once 

#include <string>
#include <vector>
#include "../scanner/token.hpp"

struct ErrorHandler {
private:
    std::string file_name;
    std::vector<std::pair<Token, std::string>> compiler_errors;
    ErrorHandler() {}
    ~ErrorHandler() = default;
    std::vector<std::string> file_contents;

public:
    // setters
    void set_file_name(std::string file_name);
    
    void set_file_contents(std::vector<std::string> &file_contents);

    // copy constructor
    ErrorHandler(const ErrorHandler&) = delete;
    // copy assignment operator
    ErrorHandler& operator=(const ErrorHandler&) = delete;
    // move operation
    ErrorHandler(ErrorHandler&&) = delete;
    // move assignment operator

    ErrorHandler& operator=(const ErrorHandler&&) = delete;

    static ErrorHandler& get_instance() {
        static ErrorHandler instance;
        return instance;
    }
    void report_compile_error(std::string message, Token token);
    void report_runtime_error(std::string message, Token token);
    std::string format_err_message(Token &token, std::string &message);
    void show_compile_error(); 
    void clear_errors();
};
