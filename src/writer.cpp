#include "writer.h"
#include <fstream>
#include <algorithm>

void Writer::writeProgram(std::vector<Token> &program, std::string fileName, int bufferSize) {
    std::fstream fs(fileName, std::fstream::out);

    fs << ".global main" << "\n.data\npc: .asciz \"%c\"\n.bss\n" << "buffer: .skip " << bufferSize << "\n.text\nmain:\nmovq $0, %rdx\n";

    // Rdx is used as pointer
    std::for_each(program.begin(), program.end(), [&fs](const Token &operation) {
//        fs << operation.opCode << " " << operation.param << "\n";
    });

    return;
}
