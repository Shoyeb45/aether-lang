#include "aether_class.hpp"

std::string AetherInstance::to_string() {
    return aether_class->name + " instance";
}

std::string AetherClass::to_string() {
    return name;
}

int AetherClass::arity() {
    return 0;
}

RuntimeValue AetherClass::call(Interpreter *interpreter, const std::vector<RuntimeValue> &args) {
    AetherInstance instance(this);
    return std::make_shared<AetherInstance>(instance);
}