//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTFUNCTIONCALLNODE_H
#define ASSIGNMENT_5_ASTFUNCTIONCALLNODE_H


#include "ASTExpressionNode.h"
#include "ASTActualParametersNode.h"

class ASTFunctionCallNode : public ASTExpressionNode{
public:
    ASTExpressionNode * Identifier;
    ASTActualParametersNode * Parameters;

    ASTFunctionCallNode(ASTExpressionNode * identifier, ASTActualParametersNode * params){
        Identifier = identifier;
        Parameters = params;
    }
    virtual ~ASTFunctionCallNode(){}
    virtual void Accept(Visitor *v){
        v->visit(this);
    }
};
#endif //ASSIGNMENT_5_ASTFUNCTIONCALLNODE_H
