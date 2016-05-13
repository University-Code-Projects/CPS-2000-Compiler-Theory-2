//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTASSIGNMENTNODE_H
#define ASSIGNMENT_5_ASTASSIGNMENTNODE_H

#include "ASTStatementNode.h"

class ASTAssignmentNode : public ASTStatementNode{

public:
    ASTExpressionNode * Identifier;
    ASTExpressionNode * Expr;

    ASTAssignmentNode(ASTExpressionNode *ident, ASTExpressionNode *expr){
        Identifier= ident;
        Expr = expr;
    }
    virtual  ~ASTAssignmentNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTASSIGNMENTNODE_H
