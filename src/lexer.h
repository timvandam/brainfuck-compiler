#pragma once

#include <vector>
#include <string>
#include "token.h"

namespace Lexer {
    std::vector<Token> read(std::string &fileName);
}
