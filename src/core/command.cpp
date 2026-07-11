#include "command.hpp"
#include "utils.hpp"
#include <iostream>
#include "../generated/version.hpp"
#include "../evaluator/evaluator.hpp"
#include "../exceptions/error_handler.hpp"
#include "../executor/executor.hpp"
#include "../interpreter/interpreter.hpp"
#include "../parser/parser.hpp"
#include "../resolver/resolver.hpp"
#include "../scanner/scanner.hpp"

std::vector<Token> scan(std::vector<std::string> &file_contents) {
    auto tokens = LexicalScanner::scan_file(file_contents);
    ErrorHandler::get_instance().show_compile_error();

    return tokens;
}

void eval_command(int len, char *args[]) {
    if (len < 2) {
        display_help_message();
        return;
    }

    const std::string command = args[1];

    if (len == 2) {
        if (command == "help") {
            display_help_message();
        } else if (command == "version") {
            std::cout << "aether " << AETHER_VERSION << "\n";

        } else {
            std::cout << "\033[31mInvalid Command\033[0m: " << command << "\n";
            display_help_message();
        }
        return;
    }

    const std::string file_name = args[2];
    verify_file_name(file_name);
    std::vector<std::string> file_contents = read_file_contents(file_name);

    ErrorHandler &err_handler = ErrorHandler::get_instance();
    err_handler.set_file_name(file_name);
    err_handler.set_file_contents(file_contents);

    if (command == "run") {
        auto tokens = scan(file_contents);
        Parser *parser = new Parser(tokens);

        std::vector<Stmt *> stmts = parser->parse_stmt();
        err_handler.show_compile_error();

        Interpreter *interpreter = new Interpreter(stmts);
        Resolver *resolver = new Resolver(interpreter);

        resolver->resolve();
        err_handler.show_compile_error();

        interpreter->execute();
    } else if (command == "tokenize") {
        std::vector<Token> tokens = LexicalScanner::scan_file(file_contents);

        bool is_error = false;
        for (auto &token : tokens) {
            if (token.is_error()) {
                err_handler.report_compile_error(token.to_lexical_error(), token);
                continue;
            }
            std::cout << token << "\n";
        }

        err_handler.show_compile_error();
    } else {
        std::cout << "Invalid Command\n";
        display_help_message();
    }
}