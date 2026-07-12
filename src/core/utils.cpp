#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> read_file_contents(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error reading file: " << filename << std::endl;
        std::exit(1);
    }

    std::vector<std::string> file_contents;

    std::string line;
    while (std::getline(file, line)) {
        file_contents.push_back(line);
    }
    return file_contents;
}

inline const std::string WHITESPACE = " \n\r\t\f\\v";

std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

std::string normalize_number_literal(const std::string &num) {
    std::string str_num = std::to_string(std::stod(num));

    while (!str_num.empty() && str_num.back() == '0') {
        str_num.pop_back();
    }

    if (str_num.back() == '.')
        str_num += "0";
    return str_num;
}

std::string normalize_number_literal(const double num) {
    std::string str_num = std::to_string(num);

    while (!str_num.empty() && str_num.back() == '0') {
        str_num.pop_back();
    }

    if (!str_num.empty() && str_num.back() == '.')
        str_num.pop_back();

    return str_num;
};

void verify_file_name(const std::string &file_name) {
    int dot_idx = file_name.find_last_of('.');

    if (dot_idx == std::string::npos) {
        std::cerr << "\033[31m[Invalid File] \033[0mPlease provide file with extension '.ae'\n";
        std::exit(1);
    }
    std::string extension = file_name.substr(dot_idx + 1);
    if (extension == "ae")
        return;

    std::cerr << "\033[31m[Invalid File Extension] \033[0mPlease provide file with extension '.ae'\n";
    std::exit(1);
}

void display_help_message() {
    std::cout << "Usage: aether [OPTIONS] INPUT\n\n";
    std::cout << "Options:\n";
    std::cout << "\thelp                      \t- Display this message\n";
    std::cout << "\tversion                   \t- Display aether version\n";
    std::cout << "\trun      <filename.ae>    \t- Execute aether source code\n";
    std::cout << "\ttokenize <filename.ae>    \t- Get the tokens of aether source code\n";
}