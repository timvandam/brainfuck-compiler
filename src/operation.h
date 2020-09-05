#pragma once

struct Operation {
    enum OpCode {
        NOOP,
        ADD,
        SUBTRACT,
        ADD_POINTER,
        SUBTRACT_POINTER,
        PRINT,
        SCAN,
        LOOP_START,
        LOOP_END
    };

    OpCode opCode;
    int param;

    /**
     * Combines this ADD/SUBTRACT or ADD_POINTER/SUBTRACT_POINTER operation with another.
     * Changes this operation.
     * @returns boolean indicating whether a combination happened
     */
    bool combineArithmetic(Operation &op);

private:
    /**
     * Helper method that combines two operations that do arithmetic.
     * The operation is not checked here. Make sure to do it beforehand.
     * This might result in param becoming 0. That case must be handled manually.
     */
    void combineArithmetic(Operation &op, OpCode positiveOp, OpCode negativeOp);
};
