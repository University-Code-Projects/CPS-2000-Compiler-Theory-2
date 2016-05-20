//
// Created by cps200x on 5/7/16.
//

#include "XMLPrint.h"

//XMLPrint *v = new XMLPrint();

XMLPrint::XMLPrint() {}

void XMLPrint::visit(ASTNode *node) {}

void XMLPrint::visit(ASTExpressionNode *node) {}

void XMLPrint::visit(ASTStatementNode *node) {}

void XMLPrint::visit(ASTProgramNode *node) {
    this->out = "";
    this->indent = 0;
    //std::cout << "Number of Nodes :" << node->statements.size() <<std::endl;
    std::cout << "<Program>" << std::endl;
    int j = node->statements.size();
    for(int i =0; i < j; i++){
        node->statements.at(i)->Accept(this);
    }

    std::cout  << this->out;
    std::cout << "</Program>" << std::endl;
}

void XMLPrint::visit(ASTIntegerNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Integer>";
    this->out+= std::to_string(node->value);
    this->out+= "</Integer>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTFloatNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Real>";
    this->out+= std::to_string(node->value);
    this->out+= "</Real>\n";
    this->indent = this->indent -4;

}

void XMLPrint::visit(ASTBoolNode *node) {
    this->indent =this-> indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Boolean>";
    if(node->value == true){
        this->out += "true";
    }else{
        this->out += "false";
    }
    //this->out+= std::to_string(node->value);
    this->out+= "</Boolean>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTStringNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<String>";
    this->out+= node->value;
    this->out+= "</String>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTBinaryNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<BinExprNode>\n";


    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Operator>'";
    if(node->operation == ">"){
        this->out += "Greater Than";
    }else if(node->operation == "<"){
        this->out += "Less Than";
    }else if(node->operation == "=="){
        this->out += "Equal";
    }else if(node->operation == ">="){
        this->out += "Greater or Equal To";
    }else if(node->operation == "<="){
        this->out += "Less or Equal To";
    }else if(node->operation == "!="){
        this->out += "Not Equal To";
    }else{
        this->out+= (node->operation);
    }
    this->out += "'</Operator>\n";
    this->indent = this->indent -4;

    //if(node->lhs !)
    node->lhs->Accept(this);
    if(node->rhs != nullptr){
        node->rhs->Accept(this);
    }

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</BinExprNode>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTIdentifierNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Identifier>";
    this->out+= node->value;
    this->out+= "</Identifier>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTVariableDeclNode *node) {
    this->indent = this->indent+4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Declaration>\n";
    node->Identifier->Accept(this);
    node->Expr->Accept(this);
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Declaration>\n";
    this->indent = this->indent -4;

}

void XMLPrint::visit(ASTAssignmentNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Assignment>\n";
    node->Identifier->Accept(this);
    node->Expr->Accept(this);
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Assignment>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTWriteNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Write>\n";
    if (node->Expr != nullptr) {
        node->Expr->Accept(this);
    } else {
       // std::cerr << "Null Expression" << std::endl;
    }
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }

    this->out+= "</Write>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTReturnNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Return>\n";
    node->Expr->Accept(this);
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Return>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTFormalParameterNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Parameter>\n";
    node->Identifier->Accept(this);
    for(int i =0; i < this->indent+4; i++){
        this->out+= " ";
    }
    this->out += "<Type>";
    this->out+= node->Type;
    this->out+= "</Type>\n";
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Parameter>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTFunctionDeclNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Function_Declaration>\n";
    node->Identifier->Accept(this);
    if(node->Parameters != nullptr){
        node->Parameters->Accept(this);
    }
    for(int i =0; i < this->indent+4; i++){
        this->out+= " ";
    }
    this->out += "<Type>";
    this->out+= node->Type;
    this->out+= "</Type>\n";
    if(node->Block != nullptr){
        node->Block->Accept(this);
    }
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Function_Declaration>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTFormalParametersNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Formal_Parameters>\n";

    int j = node->parameters.size();
    for(int i =0; i < j; i++){
        node->parameters.at(i)->Accept(this);
    }
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Formal_Parameters>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTIfStatementNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<If_Statement>\n";
    node->Expression->Accept(this);
    node->Block->Accept(this);


    if(node->ElseBlock != nullptr){
        for(int i =0; i < this->indent; i++){
            this->out+= " ";
        }
        this->out += "<Else_Statement>\n";
        node->ElseBlock->Accept(this);
        for(int i =0; i < this->indent; i++){
            this->out+= " ";
        }
        this->out += "</Else_Statement>\n";
    }

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</If_Statement>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTWhileNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<While_Statement>\n";
    node->Expr->Accept(this);
    node->Block->Accept(this);

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "</While_Statement>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTBlockNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Block>\n";

    int j = node->statements.size();
    for(int i =0; i < j; i++){
        node->statements.at(i)->Accept(this);
    }

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Block>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTActualParametersNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Actual_Parameter>\n";

    int j = node->parameters.size();

    for(int i =0; i < j; i++){
        node->parameters.at(i)->Accept(this);
    }

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }

    this->out+= "</Actual_Parameter>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTFunctionCallNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Function_Call>\n";

    node->Identifier->Accept(this);
    node->Parameters->Accept(this);

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Function_Call>\n";
    this->indent = this->indent -4;
}

void XMLPrint::visit(ASTUnaryNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }


    this->out += "<Unary_Expression>\n";

    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Operator>'";
    this->out+= (node->operation);
    this->out += "'</Operator>\n";
    this->indent = this->indent -4;


    node->lhs->Accept(this);

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Unary_Expression>\n";
    this->indent = this->indent -4;

}

void XMLPrint::visit(ASTSubExpressionNode *node) {
    this->indent = this->indent +4;
    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out += "<Sub_Expression>\n";

    node->Expr->Accept(this);

    for(int i =0; i < this->indent; i++){
        this->out+= " ";
    }
    this->out+= "</Sub_Expression>\n";
    this->indent = this->indent -4;
}
