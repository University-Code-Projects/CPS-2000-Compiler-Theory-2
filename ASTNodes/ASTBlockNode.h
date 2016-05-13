//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTBLOCKNODE_H
#define ASSIGNMENT_5_ASTBLOCKNODE_H

#include "ASTStatementNode.h"

class ASTBlockNode : public ASTStatementNode{
public:
    std::vector<ASTStatementNode*> statements;

    ASTBlockNode(){
        while(!statements.empty()){
            statements.pop_back();
        }
    }
    void addStatement(ASTStatementNode* statement){
        statements.push_back(statement);
    }
    virtual ~ASTBlockNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }

};

#endif //ASSIGNMENT_5_ASTBLOCKNODE_H
