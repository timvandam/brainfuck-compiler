#include <iostream>

#include "lexer.h"
#include "writer.h"
#include "parser.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "[ERROR] Please provide a file to compile." << std::endl;
        std::cout << "\tUsage: bf <inputFile> [<outputFile>]" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::string outputFileName = argv[2] ? argv[2] : "out.s";

    std::vector<Lexer::Token> tokens = Lexer::read(fileName);
    std::vector<Parser::Operation> program = Parser::parse(tokens);
    std::cout << "[INFO] Optimized the program to " << program.size() << " instructions." << std::endl;

    Writer::writeProgram(program, outputFileName);

    return 0;
}
