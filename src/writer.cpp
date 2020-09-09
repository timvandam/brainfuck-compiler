#include "writer.h"
#include <fstream>
#include <algorithm>
#include <iostream>

const std::string PTR = "%r15";
const std::string BUFFER = "buffer";

void Writer::writeProgram(std::vector<Parser::Operation> &program, const std::string &fileName, int bufferSize) {
    std::fstream fs(fileName, std::fstream::out);

    fs << ".global main\n"
          ".data\n"
          ".bss\n"
          << BUFFER << ": .skip " << bufferSize << "\n"
           ".text\n"
           "main:\n"
           "movq $0, " << PTR << "\n";

    // Rdx is used as pointer
    /*std::for_each(program.begin(), program.end(), [&fs](const Parser::Operation &operation) {
        fs << operation.toString() << "\n";
    });*/

    std::for_each(program.begin(), program.end(), [&fs](const Parser::Operation &operation) {
        fs << operation.toAsm(PTR, BUFFER);
        fs << "\n";
    });

    std::cout << "[INFO] Wrote assembly" << std::endl;
}
