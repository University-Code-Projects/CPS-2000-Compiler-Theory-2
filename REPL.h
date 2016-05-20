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
    ASTStatementNode *funcCall;

    int in;
    float fl;
    bool bo;
    std::string str;
    std::string eval;
    Lexer *lex;
    Parser * parser;
    InterpreterExecution *i;


public:
    REPL();
    void evalution();
    bool loadFile(std::string name);//used to load a file
    void cmdFunctionPrint();//print all the commands
    void ansResult(SymbolTable::primitive_type type);//change the value of ans in the symbol table
};


#endif //ASSIGNMENT_5_REPL_H
