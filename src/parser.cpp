#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <regex>
#include "parser.h"

std::vector<Parser::Operation> Parser::parse(const std::vector<Lexer::Token> &program) {
    // Stack containing scopes. Bottom one is the global scope. Above will be loops.
    std::stack<std::vector<Operation>> scope;
    scope.push(std::vector<Operation>{});
    for (const Lexer::Token &t : program) {
        std::vector<Operation> &cursor = scope.top();
        switch (t) {
            case Lexer::Token::ADD:
                cursor.emplace_back(OpCode::ADD, 1);
                break;
            case Lexer::Token::SUB:
                cursor.emplace_back(OpCode::ADD, -1);
                break;
            case Lexer::Token::INC_POINTER:
                cursor.emplace_back(OpCode::ADD_PTR, 1);
                break;
            case Lexer::Token::DEC_POINTER:
                cursor.emplace_back(OpCode::ADD_PTR, -1);
                break;
            case Lexer::Token::PRINT:
                cursor.emplace_back(OpCode::PRINT);
                break;
            case Lexer::Token::SCAN:
                cursor.emplace_back(OpCode::SCAN);
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
                Operation::Scope loopContent = scope.top(); // We can't do a reference cuz we poppin'
                scope.pop();
                scope.top().emplace_back(OpCode::LOOP, loopContent);
                break;
        }
    }

    if (scope.size() > 1) {
        std::cout << "[ERROR] Uncompleted loops found." << std::endl;
        exit(1);
    }

    std::cout << "[INFO] Parsed program (OPS = " << scope.top().size() << ")" << std::endl;
    return scope.top();
}

Parser::Operation::Operation(OpCode opCode) : opCode(opCode) {}

Parser::Operation::Operation(OpCode opCode, int param) : opCode(opCode), param(param) {}

Parser::Operation::Operation(Parser::OpCode opCode, Parser::Operation::Scope &param) : opCode(opCode), param(param) {}

std::string Parser::Operation::toString() const {
    switch (opCode) {
        case ADD: {
            std::string str = "Add(";
            str += std::to_string(std::get<int>(param));
            str += ")";
            return str;
        }
        case ADD_PTR: {
            std::string str = "AddPtr(";
            str += std::to_string(std::get<int>(param));
            str += ")";
            return str;
        }
        case PRINT:
            return "Print()";
        case SCAN:
            return "Scan()";
        case LOOP:
            std::string str = "Loop[\n";
            const auto &scope = std::get<Scope>(param);
            for (const Operation &op : scope) {
                str += op.toString();
                str += "\n";
            }
            // Add \t
            str = std::regex_replace(str, std::regex{"\n"}, "\n\t");
            // Remove last \t (before the ])
            str = std::regex_replace(str, std::regex{"\t$"}, "");
            str += "]";
            return str;
    }
    return "Invalid";
}

std::string Parser::Operation::toAsm(const std::string &PTR, const std::string &BUFFER) const {
    std::string result;
    std::string cell = BUFFER + "(" + PTR + ")";
    switch (opCode) {
        case ADD:
            result += "addq $" + std::to_string(std::get<int>(param)) + ", " + cell;
            break;
        case ADD_PTR:
            result += "addq $" + std::to_string(std::get<int>(param)) + ", " + PTR;
            break;
        case PRINT:
            result += "movq " + cell + ", %rdi\n"
                                       "call putchar";
            break;
        case SCAN:
            result += "call getchar\n"
                      "movb %al, " + cell;
            break;
        case LOOP:
            std::string loopLabel = "Loop" + std::to_string(loopCount++);
            result += loopLabel + ":\n"; // loop label
            const auto &scope = std::get<Scope>(param);
            std::for_each(scope.begin(), scope.end(), [&result, &PTR, &BUFFER](const Operation &op) {
                result += op.toAsm(PTR, BUFFER);
                result += "\n";
            });
            result += "cmpb $0, " + cell + "\n"; // cmp
            result += "jne " + loopLabel; // jump back
            break;
    }
    return result;
}
