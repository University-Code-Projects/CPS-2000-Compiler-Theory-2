//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTVARIABLEDECLNODE_H
#define ASSIGNMENT_5_ASTVARIABLEDECLNODE_H

#include "ASTStatementNode.h"

class ASTVariableDeclNode : public ASTStatementNode{
public:
    ASTExpressionNode * Identifier;
    ASTExpressionNode * Expr;
    std::string Type;

    ASTVariableDeclNode(ASTExpressionNode * identifier, ASTExpressionNode * expr, std::string type) {
        Identifier = identifier;
        Expr = expr;
        Type = type;
    }
    virtual ~ASTVariableDeclNode(){}
    virtual void Accept(Visitor *v) {
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTVARIABLEDECLNODE_H
