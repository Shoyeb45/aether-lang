#pragma once

#include <string>
#include "../parser/ast_node.hpp"
#include "../scanner/token.hpp"
#include "../core/runtime_value.hpp"

struct Evaluator {
    ASTNode* root;
    Evaluator(ASTNode* root): root(root) {}
    RuntimeValue evaluate(ASTNode* node);
    RuntimeValue perform_binary_opration(Binary* binary_node);
    RuntimeValue perform_unary_operation(Unary *unary_node);
public:
    std::string evaluate();
};