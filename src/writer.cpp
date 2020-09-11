#include "writer.h"
#include <fstream>
#include <algorithm>
#include <iostream>

const std::string PTR = "%r15";
const std::string BUFFER = "buffer";
const std::string CELL = BUFFER + "(" + PTR + ")";

void Writer::writeProgram(std::vector<Parser::Operation> &program, const std::string &fileName, int bufferSize) {
    std::fstream fs(fileName, std::fstream::out);

    fs << ".global main\n"
          ".bss\n"
       << BUFFER << ": .skip " << bufferSize << "\n"
                                                ".text\n"
                                                "main:\n"
                                                "movq $0, " << PTR << "\n";

    std::for_each(program.begin(), program.end(), [&fs](const Parser::Operation &operation) {
        fs << writeInstruction(operation);
        fs << "\n";
    });

    std::cout << "[INFO] Wrote assembly" << std::endl;
}

int loopCount = 0; // Used to name loops
std::string Writer::writeInstruction(const Operation &operation) {
    const Operation::Param &param = operation.param;
    std::string result;
    switch (operation.opCode) {
        case ADD:
            result += "addb $" + std::to_string(std::get<int>(param)) + ", " + CELL;
            break;
        case ADD_PTR:
            result += "addq $" + std::to_string(std::get<int>(param)) + ", " + PTR;
            break;
        case PRINT:
            result += "movb " + CELL + ", %dil\n";
            result += "call putchar";
            break;
        case SCAN:
            result += "call getchar\n";
            result += "movb %al, " + CELL;
            break;
        case LOOP: {
            int id = loopCount++;
            std::string loopStart = "s" + std::to_string(id);
            std::string loopEnd = "e" + std::to_string(id);

            const auto &scope = std::get<Operation::Scope>(param);

            // If 0, skip to loopEnd
            result += "cmpb $0, " + CELL + "\n";
            result += "je " + loopEnd + "\n";

            // Loop Starts here
            result += loopStart + ":\n";
            std::for_each(scope.begin(), scope.end(), [&result](const Operation &operation) {
                result += writeInstruction(operation);
                result += "\n";
            });

            // Loop back if needed
            result += "cmpb $0, " + CELL + "\n";
            result += "jne " + loopStart + "\n";

            // EOL (end of loop)
            result += loopEnd + ":";

            break;
        }
        case CLEAR:
            result += "movb $0, " + CELL;
            break;
    }
    return result;
}
