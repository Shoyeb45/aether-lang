#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// custom headers
#include "core/utils.hpp"
#include "scanner/scanner.hpp"


int main(int argc, char *argv[]) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    if (argc < 3) {
        std::cerr << "Usage: ./your_program tokenize <filename>" << std::endl;
        return 1;
    }

    const std::string command = argv[1];

    if (command == "tokenize") {
        std::vector<std::string> file_contents = read_file_contents(argv[2]);

        auto [tokens, errors] = scan_file(file_contents);

        for (auto &token: tokens) {
            std::cout << token << "\n";
        }
        
        if (errors.size() > 0) {
            for (auto &err: errors) {
                std::cerr << err << "\n";  
            }
            exit(65);
        }

    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
