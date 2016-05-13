//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTIFSTATEMENTNODE_H
#define ASSIGNMENT_5_ASTIFSTATEMENTNODE_H

#include "ASTStatementNode.h"

class ASTIfStatementNode : public ASTStatementNode{
public:
    ASTExpressionNode * Expression;
    ASTStatementNode * Block;
    ASTStatementNode * ElseBlock;

    ASTIfStatementNode(ASTExpressionNode * expr, ASTStatementNode * block , ASTStatementNode * elseBlock){
        Expression = expr;
        Block = block;
        ElseBlock = elseBlock;
    }
    virtual ~ASTIfStatementNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};


#endif //ASSIGNMENT_5_ASTIFSTATEMENTNODE_H
