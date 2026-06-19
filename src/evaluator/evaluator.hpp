#pragma once

#include <string>
#include <vector>
#include "../parser/ast_node.hpp"
#include "../scanner/token.hpp"
#include "../core/runtime_value.hpp"

struct Evaluator {
    ASTNode* root;
    std::vector<std::string> errors;
    Evaluator(ASTNode* root): root(root) {}
    RuntimeValue evaluate(ASTNode* node);
    RuntimeValue perform_binary_opration(Binary* binary_node);
    RuntimeValue perform_unary_operation(Unary *unary_node);
    void push_error(std::string message, Token &token);

public:
    std::string evaluate();
};