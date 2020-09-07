#pragma once

#include <vector>
#include <string>
#include "lexer.h"
#include "parser.h"

/**
 * Namespace responsible for writing assembly.
 */
namespace Writer {
    /**
     * Writes the program, using a buffer of X bytes.
     */
    void writeProgram(std::vector<Parser::Operation> &program, const std::string &fileName, int bufferSize = 1000);
}
