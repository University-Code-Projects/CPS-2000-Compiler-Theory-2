//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTFUNCTIONDECLNODE_H
#define ASSIGNMENT_5_ASTFUNCTIONDECLNODE_H

#include "ASTStatementNode.h"

class ASTFunctionDeclNode : public ASTStatementNode{
public:
    ASTExpressionNode * Identifier;
    ASTFormalParametersNode * Parameters;
    std::string Type;
    ASTStatementNode * Block;

    ASTFunctionDeclNode(ASTExpressionNode * identifier, ASTFormalParametersNode * params, std::string type, ASTStatementNode *block){
        Identifier = identifier;
        Parameters = params;
        Type = type;
        Block = block;
    }
    virtual ~ASTFunctionDeclNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTFUNCTIONDECLNODE_H
