#include <algorithm>
#include <iostream>
#include "optimizer.h"

void Optimizer::optimize(Parser::Operation::Scope &program) {
    std::for_each(program.begin(), program.end(), [](Operation &operation) {
        if (operation.opCode == OpCode::LOOP) {
            auto &scope = (Operation::Scope&)(operation.param);
            if (scope.size() == 1 && scope[0].opCode == OpCode::ADD && std::get<int>(scope[0].param) == -1) {
                operation.opCode = OpCode::CLEAR; // Replace loop with clear
            } else optimize(scope);
        }
    });
    mergeAdd(program);
    mergeAddPtr(program);
}

void Optimizer::mergeAdd(Parser::Operation::Scope &program) {
    for (auto it = program.begin(); it != program.end() - 1; ++it) {
        Operation &current = *it;
        Operation &next = *(it + 1);
        if (current.opCode != OpCode::ADD || next.opCode != OpCode::ADD) continue;
        // They are both add. Let's merge them!
        int count = std::get<int>(current.param) + std::get<int>(next.param);
        current.param = count;
        program.erase(it + 1);
        it--;
    }
}

void Optimizer::mergeAddPtr(Parser::Operation::Scope &program) {
    for (auto it = program.begin(); it != program.end() - 1; ++it) {
        Operation &current = *it;
        Operation &next = *(it + 1);
        if (current.opCode != OpCode::ADD_PTR || next.opCode != OpCode::ADD_PTR) continue;
        // They are both add. Let's merge them!
        int count = std::get<int>(current.param) + std::get<int>(next.param);
        current.param = count;
        program.erase(it + 1);
        it--;
    }
}
