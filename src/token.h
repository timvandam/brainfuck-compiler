#pragma once

#include <string>

struct Token {
    enum OpCode {
        NOOP,
        ADD,
        SUBTRACT,
        ADD_POINTER,
        SUBTRACT_POINTER,
        PRINT,
        SCAN,
        LOOP_START,
        LOOP_END
    };

    OpCode opCode;
};
