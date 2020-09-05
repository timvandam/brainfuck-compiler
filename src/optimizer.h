#pragma once

#include <vector>
#include "operation.h"

namespace Optimizer {
    /**
     * Optimize the program by combining consecutive ADD/SUBTRACT instructions.
     */
    void combineArithmetic (std::vector<Operation> &program);
}
