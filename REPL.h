//
// Created by cps200x on 5/18/16.
//

#ifndef ASSIGNMENT_5_REPL_H
#define ASSIGNMENT_5_REPL_H

#include "Parser.h"
#include "Lexer.h"

class REPL{
private :
    float ans;
    std::string eval;
    Lexer *lex;
    Parser * parser;

public:
    REPL();
    void evalution();
    void cmdFunctionPrint();
};


#endif //ASSIGNMENT_5_REPL_H
