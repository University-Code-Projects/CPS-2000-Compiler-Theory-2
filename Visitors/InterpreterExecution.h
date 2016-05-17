//
// Created by cps200x on 5/16/16.
//

#ifndef ASSIGNMENT_5_INTERPRETEREXECUTION_H
#define ASSIGNMENT_5_INTERPRETEREXECUTION_H



#include "Visitor.h"
#include "../SymbolTable.h"
#include "../ASTNodes/Include.h"

class InterpreterExecution : public Visitor{
private:

    SymbolTable st;
    SymbolTable::primitive_type Type;

    SymbolTable::primitive_type funcType;

    std::vector<std::map< std::string,SymbolTable::varValue>> funcParam;
    std::map< std::string,SymbolTable::varValue > para;

    std::string ident;
    std::string funcName;
    std::string operation;

    bool exists;
    bool param;
    bool ret;
    bool func;

    int iValue;
    float rValue;
    bool bValue;
    std::string sValue;

    ASTStatementNode * funcCall;

public:

    InterpreterExecution();

    void typeSet(std::string type);

    std::string typePrint(SymbolTable::primitive_type type);

    std::string valuePrint(SymbolTable::primitive_type type);

    void Error(std::string error);

    virtual void visit(ASTNode *);

    virtual void visit(ASTProgramNode *);
    virtual void visit(ASTExpressionNode *);
    virtual void visit(ASTStatementNode *);

    virtual void visit(ASTBinaryNode *);
    virtual void visit(ASTUnaryNode *);

    virtual void visit(ASTSubExpressionNode *);
    virtual void visit(ASTFunctionCallNode *);

    virtual void visit(ASTIntegerNode *);
    virtual void visit(ASTFloatNode *);
    virtual void visit(ASTBoolNode *);
    virtual void visit(ASTStringNode *);

    virtual void visit(ASTIdentifierNode *);

    virtual void visit(ASTFormalParameterNode *);
    virtual void visit(ASTFormalParametersNode *);

    virtual void visit(ASTActualParametersNode *);

    virtual void visit(ASTVariableDeclNode *);
    virtual void visit(ASTAssignmentNode *);
    virtual void visit(ASTWriteNode *);
    virtual void visit(ASTReturnNode *);
    virtual void visit(ASTFunctionDeclNode *);
    virtual void visit(ASTIfStatementNode *);
    virtual void visit(ASTWhileNode *);
    virtual void visit(ASTBlockNode *);

};

#endif //ASSIGNMENT_5_INTERPRETEREXECUTION_H
