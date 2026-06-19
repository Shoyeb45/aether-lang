#include "evaluator.hpp"
#include "../core/runtime_value.hpp"
#include "../core/utils.hpp"
#include <string>

std::string Evaluator::evaluate() {
    if (!root)
        return "";
    RuntimeValue result = this->evaluate(root);

    if (is_true(result)) {
        return "true";
    } else if (is_false(result)) {
        return "false";
    } else if (is_number(result)) {
        return normalize_number_literal(std::get<double>(result));
    } else if (is_nil(result)) {
        return "nil";
    } else if (is_string(result)) {
        return std::get<std::string>(result);
    }
    return "";
}

RuntimeValue Evaluator::perform_binary_opration(Binary *binary_node) {
    RuntimeValue left_val = evaluate(binary_node->left);
    RuntimeValue right_val = evaluate(binary_node->right);
    return nullptr;
}

RuntimeValue Evaluator::evaluate(ASTNode *node) {
    if (!node)
        return nullptr;

    switch (node->type) {
    case NodeType::LITERAL:
        return static_cast<Literal *>(node)->token.get_runtime_value();
    case NodeType::GROUP:
        return evaluate(static_cast<Group *>(node)->ast_node);
    case NodeType::BINARY: {
        Binary *binary_node = static_cast<Binary *>(node);
        return perform_binary_opration(binary_node);
    }
    };
    return nullptr;
}