#pragma once

#include <utility>
#include <vector>
#include "lexer.h"

namespace Parser {
    // TODO: Offset to indicate offset from current pointer value
    struct Operation {
    };

    struct Add : Operation {
        const int count;

        explicit Add(int count = 1);
    };

    struct Sub : Operation {
        const int count;

        explicit Sub(int count = 1);
    };

    struct AddPtr : Operation {
        const int count;

        explicit AddPtr(int count = 1);
    };

    struct SubPtr : Operation {
        const int count;

        explicit SubPtr(int count = 1);
    };

    struct Loop : Operation {
        const std::vector<Operation> &scope;

        explicit Loop(const std::vector<Operation> &scope);
    };

    struct PrintChar : Operation {
        explicit PrintChar();
    };

    struct GetChar : Operation {
        explicit GetChar();
    };

    /**
     * Get a stream of operations from a stream of tokens
     */
    std::vector<Operation> parse(const std::vector<Lexer::Token> &program);

    std::string ast(const std::vector<Operation> &program);
}
