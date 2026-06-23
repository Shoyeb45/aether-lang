#pragma once

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
    FOR_STMT,
};
