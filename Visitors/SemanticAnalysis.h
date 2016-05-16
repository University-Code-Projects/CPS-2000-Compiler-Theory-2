//
// Created by cps200x on 5/13/16.
//

#ifndef ASSIGNMENT_5_SEMANTICANALYSIS_H
#define ASSIGNMENT_5_SEMANTICANALYSIS_H

//#include <algorithm.h>
#include "Visitor.h"
#include "../SymbolTable.h"
#include "../ASTNodes/Include.h"

class SemanticAnalysis : public Visitor{
private:

    SymbolTable st;
    SymbolTable::primitive_type Type;

    SymbolTable::primitive_type funcType;
    SymbolTable::primitive_type retType;

    std::vector<std::map< std::string,SymbolTable::primitive_type>> funcParam;
    std::map< std::string,SymbolTable::primitive_type > para;

    std::string ident;
    std::string funcName;
    std::string operation;

    bool exists;
    bool param;




    //bool set;

   // bool add;
   // bool ret;
   // bool func;
   // bool param;




    //std::multimap< std::string,SymbolTable::primitive_type> param;
public:

    SemanticAnalysis();

    void typeSet(std::string type);
    std::string typePrint(SymbolTable::primitive_type type);

    void Error(std::string error);

    virtual void visit(ASTNode *);

    virtual void visit(ASTProgramNode *);
    virtual void visit(ASTExpressionNode *);
    virtual void visit(ASTStatementNode *);

    virtual void visit(ASTBinaryNode *);
    virtual void visit(ASTUnaryNode *);

    virtual void visit(ASTSubExpressionNode *);
    virtual void visit(ASTFunctionCallNode *);

    virtual void visit(ASTIntegerNode *);
    virtual void visit(ASTFloatNode *);
    virtual void visit(ASTBoolNode *);
    virtual void visit(ASTStringNode *);

    virtual void visit(ASTIdentifierNode *);

    virtual void visit(ASTFormalParameterNode *);
    virtual void visit(ASTFormalParametersNode *);

    virtual void visit(ASTActualParametersNode *);

    virtual void visit(ASTVariableDeclNode *);
    virtual void visit(ASTAssignmentNode *);
    virtual void visit(ASTWriteNode *);
    virtual void visit(ASTReturnNode *);
    virtual void visit(ASTFunctionDeclNode *);
    virtual void visit(ASTIfStatementNode *);
    virtual void visit(ASTWhileNode *);
    virtual void visit(ASTBlockNode *);

};
#endif //ASSIGNMENT_5_SEMANTICANALYSIS_H
