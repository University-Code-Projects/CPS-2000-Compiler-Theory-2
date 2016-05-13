//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTSTATEMENTNODE_H
#define ASSIGNMENT_5_ASTSTATEMENTNODE_H

#include "ASTNode.h"

class ASTStatementNode : public ASTNode{
public:
    virtual ~ASTStatementNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTSTATEMENTNODE_H
