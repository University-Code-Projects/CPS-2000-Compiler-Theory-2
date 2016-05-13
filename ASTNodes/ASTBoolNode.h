//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTBOOLNODE_H
#define ASSIGNMENT_5_ASTBOOLNODE_H

#include "ASTExpressionNode.h"

class ASTBoolNode : public ASTExpressionNode{
public:
    bool value;
    ASTBoolNode(bool num){
        value = num;
    }
    virtual ~ASTBoolNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTBOOLNODE_H
