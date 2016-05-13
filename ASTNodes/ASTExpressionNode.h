//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTEXPRESSIONNODE_H
#define ASSIGNMENT_5_ASTEXPRESSIONNODE_H

#include "ASTNode.h"
class ASTExpressionNode : public ASTNode{
public:
    virtual ~ASTExpressionNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTEXPRESSIONNODE_H
