//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTFORMALPARAMETERNODE_H
#define ASSIGNMENT_5_ASTFORMALPARAMETERNODE_H

#include "ASTExpressionNode.h"

class ASTFormalParameterNode : public ASTExpressionNode{
public:

    ASTExpressionNode * Identifier;
    std::string Type;

    ASTFormalParameterNode(ASTExpressionNode * identifier, std::string type){
        Identifier = identifier;
        Type = type;
    }
    virtual ~ASTFormalParameterNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }

};

#endif //ASSIGNMENT_5_ASTFORMALPARAMETER_H
