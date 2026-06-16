#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


std::vector<std::string> read_file_contents(const std::string& filename) {
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