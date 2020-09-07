#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include "parser.h"

std::vector<Parser::Operation> Parser::parse(const std::vector<Lexer::Token> &program) {
    // Stack containing scopes. Bottom one is the global scope. Above will be loops.
    std::stack<std::vector<Operation>> scope;
    scope.push(std::vector<Operation>{});
    for (const Lexer::Token &t : program) {
        std::vector<Operation> &cursor = scope.top();
        switch (t) {
            case Lexer::Token::ADD:
                cursor.push_back(Add{});
                break;
            case Lexer::Token::SUBTRACT:
                cursor.push_back(Sub{});
                break;
            case Lexer::Token::INC_POINTER:
                cursor.push_back(AddPtr{});
                break;
            case Lexer::Token::DEC_POINTER:
                cursor.push_back(SubPtr{});
                break;
            case Lexer::Token::PRINT:
                cursor.push_back(PrintChar{});
                break;
            case Lexer::Token::SCAN:
                cursor.push_back(GetChar{});
                break;
            case Lexer::Token::LOOP_START:
                // Create a new scope for this loop.
                scope.push(std::vector<Operation>{});
                break;
            case Lexer::LOOP_END:
                if (scope.size() == 1) {
                    std::cout << "[ERROR] Saw a loop end before a loop start" << std::endl;
                    exit(1);
                }
                // Pop the top scope, and add it in the next scope.
                std::vector<Operation> &loopContent = scope.top();
                scope.pop();
                scope.top().push_back(Loop{loopContent});
                break;
        }
    }

    if (scope.size() > 1) {
        std::cout << "[ERROR] Uncompleted loops found." << std::endl;
        exit(1);
    }

    return scope.top();
}

std::string Parser::ast(const std::vector<Operation> &program) {
    std::string result;
    std::for_each(program.begin(), program.end(), [&result](const Operation &operation) {
//        result += operation.toString();
    });
    return result;
}

Parser::Add::Add(int count) : count(count) {}

Parser::Sub::Sub(int count) : count(count) {}

Parser::AddPtr::AddPtr(int count) : count(count) {}

Parser::SubPtr::SubPtr(int count) : count(count) {}

Parser::Loop::Loop(const std::vector<Operation> &scope) : scope(scope) {}

Parser::PrintChar::PrintChar() = default;

Parser::GetChar::GetChar() = default;
