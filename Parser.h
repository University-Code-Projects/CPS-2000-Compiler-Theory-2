//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_PARSER_H
#define ASSIGNMENT_5_PARSER_H

#include "Lexer.h"
#include "ASTNodes/Include.h"


class Parser{
public:
    Parser(bool text,Lexer &lexer);//constructor
    virtual  ~Parser(){};//deconstructor

    ASTNode * Parse();//parse statements
    ASTNode * ParseRepl();//parse statements and expressions
private:
    Lexer::Token CurrToken;//current token from the lexer
    Lexer::Token Peek;
    Lexer lex;

    bool funcDecl;

    ASTStatementNode * ParseStatement();//parse statement that calls one of the following functions according to the token type

    //the functions are used to check that the tokens given are in the correct format of the ebnf function
    ASTStatementNode * ParseVariableDecl();//parse variable declaration
    ASTStatementNode * ParseAssignment();//parse variable assignment
    ASTStatementNode * ParseWriteStatement();//parse a write statement
    ASTStatementNode * ParseFunctionDecl();//parse a function declaration
    ASTStatementNode * ParseIfStatement();//parse an if statement
    ASTStatementNode * ParseWhileStatement();//parse while statement
    ASTStatementNode * ParseBlock();//parse block statement
    ASTStatementNode * ParseReturnStatement();//parse return statement


    ASTExpressionNode * ParseExpression();//parse expression which calls one of the below functions

    ASTExpressionNode * ParseIdentifier();//parse an identifier
    ASTExpressionNode * ParseSimpleExpression();//parse a simple expression
    ASTExpressionNode * ParseTerm();//parse a term
    ASTExpressionNode * ParseFactor();//parse a factor

    ASTExpressionNode * ParseBinaryOperation(int prec, ASTExpressionNode * lhs);//parse a binary operation with lhs and rhs

    ASTUnaryNode * ParseUnary();// parse a unary expression that consists of only the lhs and operator

    ASTExpressionNode * ParseFunctionCall();//parse a functino call that calls the method below to get the parametes
    ASTActualParametersNode * ParseActualParams();//parse actual parameters when a funciton call is called

    ASTFormalParametersNode * ParseFormalParams();//parse formal parametes when a function is declared
    ASTExpressionNode * ParseFormalParam();//parse a single formal parameter, called by the function above

    void * Error(const char *str);//used to print the error if a syntax error is found
};

#endif //ASSIGNMENT_5_PARSER_H
