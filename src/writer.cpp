#include "writer.h"
#include <fstream>
#include <algorithm>

void Writer::writeProgram(std::vector<Operation> &program, std::string fileName, int bufferSize) {
    std::fstream fs(fileName, std::fstream::out);

    // TODO: Pre-compile pointer locations

    fs << ".global main" << "\n.data\npc: .asciz \"%c\"\n.bss\n" << "buffer: .skip " << bufferSize << "\n.text\nmain:\nmovq $0, %rdx\n";

    // Rdx is used as pointer
    std::for_each(program.begin(), program.end(), [&fs](const Operation &operation) {
//        fs << operation.opCode << " " << operation.param << "\n";
    });

    return;
}