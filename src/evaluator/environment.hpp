#pragma once

#include "../core/runtime_value.hpp"
#include <string>
#include <unordered_map>

struct EnvironmentTable {
  private:
    std::unordered_map<std::string, RuntimeValue> table;

  public:
    void set(std::string &name, RuntimeValue value) {
        table[name] = value;
    }

    RuntimeValue get(std::string &name) {
        if (table.contains(name)) {
            return table[name];
        }
        // error handle
        return nullptr;
    }
};