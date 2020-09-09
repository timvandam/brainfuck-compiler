#pragma once

#include <vector>
#include <variant>
#include "lexer.h"

namespace Parser {
    static int loopCount = 0;

    enum OpCode {
        ADD,
        ADD_PTR,
        PRINT,
        SCAN,
        LOOP
    };

    struct Operation {
        typedef std::vector<Operation> Scope;
        typedef std::variant<int, Scope> Param;
        OpCode opCode;
        Param param;

        explicit Operation(OpCode opCode);

        Operation(OpCode opCode, int param);

        Operation(OpCode opCode, Scope &param);

        std::string toString() const;

        std::string toAsm(const std::string &PTR, const std::string &BUFFER) const;
    };

    // TODO: Offset to indicate offset from current pointer value

    /**
     * Get a stream of operations from a stream of tokens
     */
    std::vector<Operation> parse(const std::vector<Lexer::Token> &program);
}
