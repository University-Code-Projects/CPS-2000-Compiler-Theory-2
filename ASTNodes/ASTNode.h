//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTNODE_H
#define ASSIGNMENT_5_ASTNODE_H

#include "../Visitors/Visitor.h"
#include "../Visitors/XMLPrint.h"

#include <vector>

class ASTNode{
public:
    virtual ~ASTNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};

#endif //ASSIGNMENT_5_ASTNODE_H
