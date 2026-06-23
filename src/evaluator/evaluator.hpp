#pragma once

#include <string>
#include <vector>
#include "../parser/expr.hpp"
#include "../scanner/token.hpp"
#include "../core/runtime_value.hpp"
#include "environment.hpp"

struct Evaluator {
    Expr* root;
    EnvironmentTable *global = new EnvironmentTable();

    std::vector<std::string> errors;
    Evaluator(Expr* root): root(root) {}
    RuntimeValue evaluate(Expr* node);
    RuntimeValue perform_binary_opration(Binary* binary_node);
    RuntimeValue perform_unary_operation(Unary *unary_node);
    RuntimeValue perform_logical_operation(Logical *logical_node);

    void push_error(std::string message, Token &token);
    void report_error();
    
public:
    std::string evaluate();
    void set_root(Expr *root) {
        this->root = root;
    }
};