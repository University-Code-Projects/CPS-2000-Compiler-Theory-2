//
// Created by cps200x on 5/13/16.
//

#ifndef ASSIGNMENT_5_SEMANTICANALYSIS_H
#define ASSIGNMENT_5_SEMANTICANALYSIS_H

#include "Visitor.h"
#include "../SymbolTable.h"
#include "../ASTNodes/Include.h"

class SemanticAnalysis : public Visitor{
private:

    //current symbol table
    SymbolTable st;

    //current type
    SymbolTable::primitive_type Type;

    //current function type
    SymbolTable::primitive_type funcType;

    //all the parameters of the funciton
    std::vector<std::map< std::string,SymbolTable::varValue>> funcParam;

    //the current parameter of the function
    std::map< std::string,SymbolTable::varValue> para;

    //current identifier name
    std::string ident;
    //current function name
    std::string funcName;
    //current operation to be executed
    std::string operation;

    //bool exists , ,if true, the identifier should already exist in the scope
    bool exists;

    //bool param, going to add a param so just get the name of the identifier and use it in the AST visit respectively
    bool param;

public:

    SemanticAnalysis();

    //since the AST Node returns the type as a string,
    //this function is being used to convert from a string to enum of the primitive types
    void typeSet(std::string type);

    //prints the type given
    //it converts from enum defined in symbol table to a string, easier for debugging
    std::string typePrint(SymbolTable::primitive_type type);

    //report the semantic error
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
