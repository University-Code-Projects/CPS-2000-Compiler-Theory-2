//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_XMLPRINT_H
#define ASSIGNMENT_5_XMLPRINT_H

#include "Visitor.h"
#include "../ASTNodes/Include.h"

class XMLPrint : public Visitor{
private:
    int indent =0;
    std::string out = "";

public:

    XMLPrint();
    //XMLPrint(int ind, std::string output);
    virtual void visit(ASTNode *);

    virtual void visit(ASTProgramNode *);
    virtual void visit(ASTExpressionNode *);
    virtual void visit(ASTStatementNode *);

    virtual void visit(ASTBinaryNode *);
    virtual void visit(ASTUnaryNode *);

    virtual void visit(ASTSubExpressionNode *);
    virtual void visit(ASTFunctionCallNode *);

    //virtual void visit(ASTActualParams *);

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

#endif //ASSIGNMENT_5_XMLPRINT_H
