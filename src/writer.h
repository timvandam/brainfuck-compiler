#pragma once

#include <vector>
#include <string>
#include "lexer.h"
#include "parser.h"

/**
 * Namespace responsible for writing assembly.
 */
namespace Writer {
    using namespace Parser;

    /**
     * Writes the program, using a buffer of X bytes.
     */
    void writeProgram(std::vector<Parser::Operation> &program, const std::string &fileName, int bufferSize = 5000);

    std::string writeInstruction(const Operation &operation);
}
