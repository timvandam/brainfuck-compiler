#pragma once

#include <vector>
#include <string>
#include "token.h"

/**
 * Namespace responsible for writing assembly.
 */
namespace Writer {
    /**
     * Writes the program, using a buffer of X bytes.
     */
    void writeProgram(std::vector<Token> &program, std::string fileName, int bufferSize = 1000);
}
