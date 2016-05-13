//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTWHILENODE_H
#define ASSIGNMENT_5_ASTWHILENODE_H

#include "ASTStatementNode.h"

class ASTWhileNode : public ASTStatementNode{
public:
    ASTStatementNode * Block;
    ASTExpressionNode *Expr;
    ASTWhileNode(ASTExpressionNode *expr,ASTStatementNode *block){
        Expr = expr;
        Block= block;
    }
    virtual ~ASTWhileNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTWHILENODE_H
