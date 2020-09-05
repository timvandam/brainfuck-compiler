#pragma once

#include <vector>
#include <string>
#include "operation.h"

namespace Parser {
    std::vector<Operation> read(std::string &fileName);
}
