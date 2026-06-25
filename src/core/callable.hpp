#pragma once

#include "../executor/executor.hpp"
#include "../parser/stmt.hpp"
#include "runtime_value.hpp"
#include <chrono>
#include <vector>
#include <string>

struct Callable {
  public:
    virtual int arity() = 0;
    virtual std::string to_string() = 0;
    virtual RuntimeValue call(Executor *executor, const std::vector<RuntimeValue> &args) = 0;
    virtual ~Callable() = default;
};

struct ClockFunction : Callable {
  public:
    int arity() override {
        return 0;
    }

    RuntimeValue call(Executor *executor, const std::vector<RuntimeValue> &args) override {
        auto ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();

        return static_cast<double>(ms);
    }

    std::string to_string() override {
        return "<func native clock>";
    }
};

struct CustomFunction : Callable {
    FuncStmt *declaration;

    CustomFunction(FuncStmt *declaration) {
        this->declaration = declaration;
    }

    RuntimeValue call(Executor *executor, const std::vector<RuntimeValue> &args) override {
        EnvironmentTable *env = new EnvironmentTable(executor->evaluator->global);

        if (declaration->params.size() != args.size()) {
            // error, std::exit(70) ? maybe
            return nullptr;
        }

        for (int i = 0; i < declaration->params.size(); i++) {
            env->set(declaration->params[i].lexeme, args[i]);
        }
        executor->execute_block_stmt(declaration->body, env);
        return nullptr;
    }

    int arity() {
        return (int) declaration->params.size();
    }

    std::string to_string() {
        return "<fn " + declaration->name.lexeme + ">";
    }
};