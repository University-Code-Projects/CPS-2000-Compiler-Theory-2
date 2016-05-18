//
// Created by cps200x on 5/18/16.
//

#ifndef ASSIGNMENT_5_REPL_H
#define ASSIGNMENT_5_REPL_H

#include "Parser.h"
#include "Lexer.h"
#include "SymbolTable.h"
#include "Visitors/InterpreterExecution.h"

class REPL{
private :
    std::ifstream file;
    SymbolTable st;


    float ans;
    std::string eval;
    Lexer *lex;
    Parser * parser;
//    auto node;
    //InterpreterExecution *i;


public:
    REPL();
    void evalution();
    bool loadFile(std::string name);
    void cmdFunctionPrint();
};


#endif //ASSIGNMENT_5_REPL_H
