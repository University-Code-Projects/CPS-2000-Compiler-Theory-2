//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTSUBEXPRESSIONNODE_H
#define ASSIGNMENT_5_ASTSUBEXPRESSIONNODE_H

#include "ASTExpressionNode.h"

class ASTSubExpressionNode : public ASTExpressionNode{
public:
    ASTExpressionNode *Expr;

    ASTSubExpressionNode(ASTExpressionNode *expr){
        Expr = expr;
    }
    virtual ~ASTSubExpressionNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTSUBEXPRESSIONNODE_H
