//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTFORMALPARAMETERSNODE_H
#define ASSIGNMENT_5_ASTFORMALPARAMETERSNODE_H

#include "ASTExpressionNode.h"

class ASTFormalParametersNode : public ASTExpressionNode{

public:
    std::vector<ASTExpressionNode*> parameters;

    ASTFormalParametersNode(){
        while(!parameters.empty()){
            parameters.pop_back();
        }
    }
    virtual ~ASTFormalParametersNode(){}
    void addParameter(ASTExpressionNode *expr){
        parameters.push_back(expr);
    }
    virtual void Accept(Visitor *v){
        v->visit(this);
    }

};

#endif //ASSIGNMENT_5_ASTFORMALPARAMETERSNODE_H
