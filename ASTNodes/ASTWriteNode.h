//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTWRITENODE_H
#define ASSIGNMENT_5_ASTWRITENODE_H

#include "ASTStatementNode.h"

class ASTWriteNode : public ASTStatementNode{
public:
    ASTExpressionNode * Expr;
    ASTWriteNode(ASTExpressionNode * expr){
        Expr= expr;
    }
    virtual ~ASTWriteNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTWRITENODE_H
