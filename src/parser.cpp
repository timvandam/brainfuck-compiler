#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "operation.h"
#include "parser.h"

std::vector<Operation> Parser::read(std::string &fileName) {
    std::fstream fs(fileName, std::fstream::in);

    if (!fs.is_open()) {
        std::cout << "[ERROR] Could not find '" << fileName << "'." << std::endl;
        exit(1);
    }

    std::cout << "[INFO] Reading file" << std::endl;

    std::vector<Operation> program;

    std::set<char> skippedChars;
    char c;
    while (fs >> c) {
        if (c == '+') program.push_back(Operation{Operation::OpCode::ADD, 1});
        else if (c == '-') program.push_back(Operation{Operation::OpCode::SUBTRACT, 1});
        else if (c == '>') program.push_back(Operation{Operation::OpCode::ADD_POINTER, 1});
        else if (c == '<') program.push_back(Operation{Operation::OpCode::SUBTRACT_POINTER, 1});
        else if (c == '[') program.push_back(Operation{Operation::OpCode::LOOP_START});
        else if (c == ']') program.push_back(Operation{Operation::OpCode::LOOP_END});
        else if (c == '.') program.push_back(Operation{Operation::OpCode::PRINT});
        else if (c == ',') program.push_back(Operation{Operation::OpCode::SCAN});
        else if (c == '#') break; // # indicates EOF. Can be used to comment stuff after the program
        else {
            std::cout << "[ERROR] Encountered invalid symbol '" << c << "'." << std::endl;
            exit(1);
        }
    }
    std::cout << "[INFO] Read program (INSTR_SIZE = " << program.size() << ")" << std::endl;
    if (!skippedChars.empty()) {
        std::string chars;
        std::for_each(skippedChars.begin(), skippedChars.end(), [&chars](char c) {
            chars += c;
            chars += ", ";
        });
        chars.resize(chars.size() - 2); // remove trailing ,
        std::cout << "[WARNING] Skipped invalid characters: " << chars << std::endl;
    }

    fs.close();

    return program;
}
