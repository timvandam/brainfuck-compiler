#include "operation.h"

bool Operation::combineArithmetic(Operation &op) {
    // Combine ADD/SUBTRACT
    if ((opCode == OpCode::ADD || opCode == OpCode::SUBTRACT) &&
        (op.opCode == OpCode::ADD || op.opCode == OpCode::SUBTRACT)) {
        combineArithmetic(op, OpCode::ADD, OpCode::SUBTRACT);
        return true;
    }

    // Combine ADD_POINTER/SUBTRACT_POINTER
    if ((opCode == OpCode::ADD_POINTER || opCode == OpCode::SUBTRACT_POINTER) &&
        (op.opCode == OpCode::ADD_POINTER || op.opCode == OpCode::SUBTRACT_POINTER)) {
        combineArithmetic(op, OpCode::ADD_POINTER, OpCode::SUBTRACT_POINTER);
        return true;
    }

    return false;
}

void Operation::combineArithmetic(Operation &op, OpCode positiveOp, OpCode negativeOp) {
    int sum = 0;
    sum += opCode == positiveOp ? param : -param;
    sum += op.opCode == positiveOp ? op.param : -op.param;

    // Combine both operations as the Current op. Remove the next
    opCode = sum == 0 ? OpCode::NOOP : (sum > 0 ? positiveOp : negativeOp);
    param = sum;
}
