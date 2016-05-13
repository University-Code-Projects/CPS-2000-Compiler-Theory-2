//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTPROGRAMNODE_H
#define ASSIGNMENT_5_ASTPROGRAMNODE_H

#include "ASTStatementNode.h"

class ASTProgramNode: public ASTStatementNode{
public:
    std::vector<ASTStatementNode*> statements;

    ASTProgramNode(){
        while(!statements.empty()){
            statements.pop_back();
        }
    }
    virtual ~ASTProgramNode(){}
    void addStatement(ASTStatementNode * node){
        statements.push_back(node);
    }
    virtual void Accept(Visitor *v){
        v->visit(this);
    }



};
#endif //ASSIGNMENT_5_ASTPROGRAMNODE_H
