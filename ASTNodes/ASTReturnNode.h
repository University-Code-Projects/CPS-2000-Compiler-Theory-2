//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTRETURNNODE_H
#define ASSIGNMENT_5_ASTRETURNNODE_H

#include "ASTStatementNode.h"

class ASTReturnNode : public ASTStatementNode{
public:
    ASTExpressionNode * Expr;

    ASTReturnNode(ASTExpressionNode * expr){
        Expr = expr;
    }
    virtual ~ASTReturnNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTRETURNNODE_H
