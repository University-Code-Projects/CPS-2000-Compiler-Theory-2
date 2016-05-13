//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTBINARYNODE_H
#define ASSIGNMENT_5_ASTBINARYNODE_H

#include "ASTExpressionNode.h"

class ASTBinaryNode : public ASTExpressionNode{
public:
    std::string operation;
    ASTExpressionNode *lhs;
    ASTExpressionNode *rhs;

    ASTBinaryNode(std::string op, ASTExpressionNode *l, ASTExpressionNode *r){
        operation = op;
        lhs = l;
        rhs = r;
    }
    virtual ~ASTBinaryNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTBINARYNODE_H
