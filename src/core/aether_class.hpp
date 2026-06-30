#pragma once 

#include <string>
#include "callable.hpp"

struct AetherInstance {
    AetherClass *aether_class;

    AetherInstance(AetherClass *aether_class)
        : aether_class(aether_class) {}

    std::string to_string();
};

struct AetherClass : Callable {
    std::string name;

    AetherClass(std::string &name)
        : name(name) {}

    std::string to_string();

    int arity();
    RuntimeValue call(Interpreter *interpreter, const std::vector<RuntimeValue> &args);
};

