//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_VISITOR_H
#define ASSIGNMENT_5_VISITOR_H

#include <iostream>

class ASTNode;
class ASTProgramNode;
class ASTExpressionNode;
class ASTStatementNode;
class ASTBinaryNode;
class ASTUnaryNode;
class ASTSubExpressionNode;
class ASTFunctionCallNode;
class ASTIntegerNode;
class ASTFloatNode;
class ASTBoolNode;
class ASTStringNode;
class ASTIdentifierNode;
class ASTFormalParametersNode;
class ASTFormalParameterNode;
class ASTVariableDeclNode;
class ASTAssignmentNode;
class ASTWriteNode;
class ASTReturnNode;
class ASTFunctionDeclNode;
class ASTIfStatementNode;
class ASTWhileNode;
class ASTBlockNode;
class ASTActualParametersNode;

class Visitor{
public:

    virtual void visit(ASTNode *)=0;

    virtual void visit(ASTProgramNode *) =0;
    virtual void visit(ASTExpressionNode *) =0;
    virtual void visit(ASTStatementNode *) =0;

    virtual void visit(ASTBinaryNode *) =0;
    virtual void visit(ASTUnaryNode *) =0;

    virtual void visit(ASTSubExpressionNode *) =0;
    virtual void visit(ASTFunctionCallNode *) =0;

    virtual void visit(ASTIntegerNode *) =0;
    virtual void visit(ASTFloatNode *) =0;
    virtual void visit(ASTBoolNode *) = 0;
    virtual void visit(ASTStringNode *) =0;

    virtual void visit(ASTIdentifierNode *) = 0;
    virtual void visit(ASTFormalParameterNode *) =0;
    virtual void visit(ASTFormalParametersNode *) =0;

    virtual void visit(ASTActualParametersNode *) =0;

    virtual void visit(ASTVariableDeclNode *) =0;
    virtual void visit(ASTAssignmentNode *) =0;
    virtual void visit(ASTWriteNode *) =0;
    virtual void visit(ASTReturnNode *) =0;
    virtual void visit(ASTFunctionDeclNode *) =0;
    virtual void visit(ASTIfStatementNode *) =0;
    virtual void visit(ASTWhileNode *) =0;
    virtual void visit(ASTBlockNode *) =0;

};

#endif //ASSIGNMENT_5_VISITOR_H
