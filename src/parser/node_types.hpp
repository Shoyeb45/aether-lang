#pragma once

#include <string>

enum NodeType {
    LITERAL,
    BINARY,
    GROUP,
    UNARY,
    VARIABLE,
    LOGICAL,
    ASSIGN,
    PRINT_STMT,
    EXPR_STMT,
    VARIABLE_STMT,
    BLOCK_STMT,
    IF_STMT,
    WHILE_STMT,
};

std::string node_type_to_string(NodeType type);