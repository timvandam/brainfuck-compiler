#pragma once

#include <vector>
#include <string>

namespace Lexer {
    enum Token {
        ADD,
        SUB,
        INC_POINTER,
        DEC_POINTER,
        PRINT,
        SCAN,
        LOOP_START,
        LOOP_END
    };

    std::vector<Token> read(std::string &fileName);
}
