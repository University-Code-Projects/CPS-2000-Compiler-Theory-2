//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTFLOATNODE_H
#define ASSIGNMENT_5_ASTFLOATNODE_H

#include "ASTExpressionNode.h"

class ASTFloatNode : public ASTExpressionNode{
public:
    float value;
    ASTFloatNode(float num){
        value = num;
    }
    virtual  ~ASTFloatNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTFLOATNODE_H
