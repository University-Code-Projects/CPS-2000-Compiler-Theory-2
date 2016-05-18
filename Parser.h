//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_PARSER_H
#define ASSIGNMENT_5_PARSER_H

#include "Lexer.h"
#include "ASTNodes/Include.h"


class Parser{
public:
    Parser(Lexer &lexer);

    //void ParserREPL(Lexer &lexer);

    virtual  ~Parser(){};

    ASTNode * Parse();

    ASTNode * ParseRepl();
private:
    Lexer::Token CurrToken;
    Lexer::Token Peek;
    Lexer lex;

    bool funcDecl;

    ASTStatementNode * ParseStatement();
    ASTExpressionNode * ParseExpression();

    ASTStatementNode * ParseVariableDecl();
    ASTStatementNode * ParseAssignment();
    ASTStatementNode * ParseWriteStatement();
    ASTStatementNode * ParseFunctionDecl();
    ASTStatementNode * ParseIfStatement();
    ASTStatementNode * ParseWhileStatement();
    ASTStatementNode * ParseBlock();
    ASTStatementNode * ParseReturnStatement();

    ASTExpressionNode * ParseIdentifier();
    ASTExpressionNode * ParseSimpleExpression();
    ASTExpressionNode * ParseTerm();
    ASTExpressionNode * ParseFactor();

    ASTExpressionNode * ParseBinaryOperation(int prec, ASTExpressionNode * lhs);

    ASTUnaryNode * ParseUnary();

    ASTActualParametersNode * ParseActualParams();
    //ASTExpressionNode * ParseActualParam();

    ASTFormalParametersNode * ParseFormalParams();
    ASTExpressionNode * ParseFormalParam();

    ASTExpressionNode * ParseFunctionCall();


    void * Error(const char *str);

};

#endif //ASSIGNMENT_5_PARSER_H
