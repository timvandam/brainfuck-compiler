#include <iostream>
#include <algorithm>

#include "operation.h"
#include "parser.h"
#include "optimizer.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "[ERROR] Please provide a file to compile." << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::vector<Operation> program = Parser::read(fileName);
    int instructionCount = program.size();
    Optimizer::combineArithmetic(program);
    std::cout << "[INFO] Optimized the program from " << instructionCount << " to " << program.size() << " instructions." << std::endl;

    // TODO: Output. TODO: Parameters

    return 0;
}
