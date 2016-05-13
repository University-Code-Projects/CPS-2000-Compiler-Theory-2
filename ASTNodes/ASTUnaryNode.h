//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTUNARYNODE_H
#define ASSIGNMENT_5_ASTUNARYNODE_H

#include "ASTExpressionNode.h"

class ASTUnaryNode : public ASTExpressionNode{

public:
    std::string operation;
    ASTExpressionNode *lhs;

    ASTUnaryNode(std::string op, ASTExpressionNode *l){
        operation = op;
        lhs = l;
    }
    virtual ~ASTUnaryNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTUNARYNODE_H
