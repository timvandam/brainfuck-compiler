#include "optimizer.h"
#include "operation.h"

void Optimizer::optimize(std::vector<Operation> &program) {
    combineArithmetic(program);
}

void Optimizer::combineArithmetic(std::vector<Operation> &program) {
    for (auto it = program.begin(); it != program.end() - 1; ++it) {
        Operation &current = *it;
        Operation &next = *(it + 1);

        if (current.combineArithmetic(next)) {
            // The next operation has been consumed during combination, so remove it.
            program.erase(it + 1);

            // If the current operation was also consumed, remove it too.
            if (current.opCode == Operation::OpCode::NOOP) program.erase(it);

            // The current operation has been optimized. Attempt to optimize it more.
            it--;
        }
    }
}
