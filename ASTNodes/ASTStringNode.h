//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTSTRINGNODE_H
#define ASSIGNMENT_5_ASTSTRINGNODE_H

#include "ASTExpressionNode.h"

class ASTStringNode : public ASTExpressionNode{
public:
    std::string value;
    ASTStringNode(std::string num){
        value = num;
    }
    virtual ~ASTStringNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTSTRINGNODE_H
