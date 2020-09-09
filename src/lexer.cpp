#include <vector>
#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "lexer.h"

std::vector<Lexer::Token> Lexer::read(std::string &fileName) {
    std::fstream fs(fileName, std::fstream::in);

    if (!fs.is_open()) {
        std::cout << "[ERROR] Could not find '" << fileName << "'." << std::endl;
        exit(1);
    }

    std::cout << "[INFO] Reading file" << std::endl;

    std::vector<Token> program;

    std::set<char> skippedChars;
    char c;
    while (fs >> c) {
        if (c == '+') program.emplace_back(Token::ADD);
        else if (c == '-') program.push_back(Token::SUB);
        else if (c == '>') program.push_back(Token::INC_POINTER);
        else if (c == '<') program.push_back(Token::DEC_POINTER);
        else if (c == '[') program.push_back(Token::LOOP_START);
        else if (c == ']') program.push_back(Token::LOOP_END);
        else if (c == '.') program.push_back(Token::PRINT);
        else if (c == ',') program.push_back(Token::SCAN);
    }
    std::cout << "[INFO] Read program (TOKENS = " << program.size() << ")" << std::endl;

    fs.close();

    return program;
}
