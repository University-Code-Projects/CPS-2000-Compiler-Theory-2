//
// Created by cps200x on 5/12/16.
//

#ifndef ASSIGNMENT_5_ASTACTUALPARAMS_H
#define ASSIGNMENT_5_ASTACTUALPARAMS_H


#include "ASTExpressionNode.h"

class ASTActualParametersNode : public ASTExpressionNode{

public:
    std::vector<ASTExpressionNode*> parameters;

    ASTActualParametersNode(){
        while(!parameters.empty()){
            parameters.pop_back();
        }
    }
    virtual ~ASTActualParametersNode(){}
    void addParameter(ASTExpressionNode *expr){
        parameters.push_back(expr);
    }
    virtual void Accept(Visitor *v){
        v->visit(this);
    }

};


#endif //ASSIGNMENT_5_ASTACTUALPARAMS_H
