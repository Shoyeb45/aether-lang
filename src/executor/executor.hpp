#pragma once

#include "../parser/stmt.hpp"
#include "../parser/expr.hpp"
#include "../evaluator/evaluator.hpp"
#include <vector>

struct Executor {
    std::vector<Stmt *> statements;
    Evaluator* evaluator = new Evaluator(nullptr);
    std::string executePrntStmt(PrintStmt *prntStmt);
    std::string executeExprStmt(ExprStmt *exprStmt);
    std::string executeStmt(Stmt *stmt);
    std::string executeVarStmt(VariableStmt *varStmt);

  public:
    Executor(std::vector<Stmt *> &statements): statements(statements) {}

    void execute();

};