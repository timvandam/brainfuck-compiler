#pragma once

#include <vector>
#include "operation.h"

namespace Optimizer {
    /**
     * Carry out all optimizations
     */
    void optimize(std::vector<Operation> &program);

    /**
     * Optimize the program by combining consecutive ADD/SUBTRACT instructions.
     */
    void combineArithmetic(std::vector<Operation> &program);
}
