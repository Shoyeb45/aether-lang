#pragma once

#include "../core/runtime_value.hpp"


struct ReturnExecption {
    RuntimeValue value;

    ReturnExecption(RuntimeValue value)
        : value(value) {}
};