//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTINTEGERNODE_H
#define ASSIGNMENT_5_ASTINTEGERNODE_H

#include "ASTExpressionNode.h"

class ASTIntegerNode : public ASTExpressionNode{
public:
    int value;
    
    ASTIntegerNode(int num){
        value = num;
    }
    virtual ~ASTIntegerNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTINTEGERNODE_H
