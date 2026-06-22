#include "executor.hpp"
#include "../parser/stmt.hpp"

std::string Executor::executeExprStmt(ExprStmt *stmt) {
    evaluator->set_root(stmt->expr);
    std::string result = evaluator->evaluate();

    if (evaluator->errors.size() > 0) {
        evaluator->report_error();
        std::exit(70);
    }
    return "";
}

std::string Executor::executeVarStmt(VariableStmt *varStmt) {
    RuntimeValue value = evaluator->evaluate(varStmt->expr);
    if (evaluator->errors.size() > 0) {
        evaluator->report_error();
        std::exit(70);
    }
    evaluator->global->set(varStmt->identifier.lexeme, value);
    return "";
}

std::string Executor::executePrntStmt(PrintStmt *prntStmt) {
    evaluator->set_root(prntStmt->expr);
    std::string result = evaluator->evaluate();

    if (evaluator->errors.size() > 0) {
        evaluator->report_error();
        std::exit(70);
    }
    std::cout << result << "\n";
    return "";
}

std::string Executor::executeStmt(Stmt *stmt) {
    switch (stmt->type) {
    case NodeType::EXPR_STMT: {
        return executeExprStmt(static_cast<ExprStmt *>(stmt));
    }
    case NodeType::PRINT_STMT: {
        return executePrntStmt(static_cast<PrintStmt *>(stmt));
    }
    case NodeType::VARIABLE_STMT: {
        return executeVarStmt(static_cast<VariableStmt *>(stmt));
    }
    case NodeType::BLOCK_STMT: {
        BlockStmt *block_stmt = static_cast<BlockStmt*>(stmt);
        std::string res = "";
        std::string intermediate_res = "";

        for (Stmt *stmt: block_stmt->stmts) {
            intermediate_res = executeStmt(stmt);
            if (intermediate_res != "") res += intermediate_res;
        }
        return res;
    }
    }
    return "";
}

void Executor::execute() {
    std::string output = "";

    for (Stmt *stmt : statements) {
        executeStmt(stmt);
        // std::cout << (output != "" ? output + "\n" : "");
    }
}