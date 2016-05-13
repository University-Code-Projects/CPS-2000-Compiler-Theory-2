//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTIDENTIFIERNODE_H
#define ASSIGNMENT_5_ASTIDENTIFIERNODE_H

#include "ASTExpressionNode.h"

class ASTIdentifierNode : public ASTExpressionNode{
public:
    std::string value;
    ASTIdentifierNode(std::string num){
        value=num;
    }
    virtual ~ASTIdentifierNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTIDENTIFIERNODE_H
