//
// Created by cps200x on 5/16/16.
//

#include "InterpreterExecution.h"

InterpreterExecution::InterpreterExecution() {

}

void InterpreterExecution::typeSet(std::string type) {
    if(type == "real"){
        this->Type = SymbolTable::primitive_type::r;
    }else if(type == "int"){
        this->Type = SymbolTable::primitive_type::i;
    }else if(type == "string"){
        this->Type = SymbolTable::primitive_type::s;
    }else if(type == "bool"){
        this->Type = SymbolTable::primitive_type::b;
    }
}

std::string InterpreterExecution::typePrint(SymbolTable::primitive_type type) {
    std::string result = "";
    switch (type){
        case 0:
            result += "int";
            break;
        case 1:
            result += "real";
            break;
        case 2:
            result += "bool";
            break;
        case 3:
            result += "string";
            break;
    }
    return result;
}

std::string InterpreterExecution::valuePrint(SymbolTable::primitive_type type) {
    std::string result = "";
    switch (type){
        case 0:
            result += std::to_string(this->iValue);
            break;
        case 1:
            result += std::to_string(this->rValue);
            break;
        case 2:
            result += std::to_string(this->bValue);
            break;
        case 3:
            result += this->sValue;
            break;
    }
    return result;
}

void InterpreterExecution::Error(std::string error) {
    std::cerr << "Semantic Error : " << error << std::endl;
    exit(1);
}

void InterpreterExecution::visit(ASTNode *node) {}

void InterpreterExecution::visit(ASTExpressionNode *node) {}

void InterpreterExecution::visit(ASTStatementNode *node) {}

void InterpreterExecution::visit(ASTProgramNode *node) {
    this->st = SymbolTable();

    this->Type = SymbolTable::primitive_type::n;
    this->funcType = SymbolTable::primitive_type::n;

    this->ident = "";
    this->operation = "";
    this->funcName = "";

    this->exists = false;

    this->funcParam.clear();
    this->para.clear();

    if(this->st.createScope() == true){
        std::cout << "Global Scope created" << std::endl;
        int j = node->statements.size();

        for(int i =0; i < j; i++){
            std::cout << i+1 <<std::endl;
            node->statements.at(i)->Accept(this);
            this->st.scopePrint();
        }
        if(this->st.deleteScope() == true){
            std::cout << "Global Scope Deleted" << std::endl;
        }else{
            Error("Could not delete Scope");
        }
    }else{
        Error("Error creating Global Scope");

    }
}

void InterpreterExecution::visit(ASTIntegerNode *node) {
    this->iValue = node->value;
    this->rValue = 0.0;
    this->bValue = false;
    this->sValue = "";
    typeSet("int");
}

void InterpreterExecution::visit(ASTFloatNode *node) {
    this->rValue = node->value;
    this->iValue = 0;
    this->bValue = false;
    this->sValue = "";
    typeSet("real");
}

void InterpreterExecution::visit(ASTBoolNode *node) {
    this->iValue = 0;
    this->rValue = 0.0;
    this->sValue = "";
    this->bValue = node->value;
    typeSet("bool");
}

void InterpreterExecution::visit(ASTStringNode *node) {
    this->iValue = 0;
    this->rValue = 0.0;
    this->bValue = false;
    this->sValue = node->value;
    typeSet("string");
}

void InterpreterExecution::visit(ASTIdentifierNode *node) {
    //this->ident = node->value;

    if(this->param){
        this->ident = node->value;
    }else {
        if (this->exists) {//check if a varibale exists
            if (this->st.inScope(node->value)) {//found in the current scope/ any previous scopes
                this->ident = node->value;
                this->Type = this->st.getType(node->value);

            } else {
                if(this->st.isParam(this->funcName,this->funcType, node->value)){
                    this->ident = node->value;

                    this->Type = this->st.getParamType(this->funcName, node->value);

                }else{
                    Error(node->value + " is not defined as a parameter");
                }
                /*
                if(this->funcName != ""){
                    std::map<std::string, SymbolTable::primitive_type >::iterator it;
                    for(int i = 0; i < this->funcParam.size(); i++){
                        for(it = this->funcParam.at(i).begin(); it !=this->funcParam.at(i).end(); it++){
                            if(it->first == node->value){
                                this->ident = node->value;

                                this->Type = it->second;
                                return;
                            }
                        }
                    }

                    Error(node->value + " is not defined as a parameter");
                }else{
                    this->ident = node->value;
                }
                 */
            }
        } else {//need to add that variable
            if (this->st.inCurrentScope(node->value)) {
                Error(node->value + " already exists in the current scope");
            } else {
                if(this->st.isParam(this->funcName,this->funcType, node->value)){
                    Error(node->value + " is already defined as a parameter");
                }else{
                    this->ident = node->value;
                }
                /*
                if(this->funcName != ""){
                    std::map<std::string, SymbolTable::primitive_type >::iterator it;
                    for(int i = 0; i < this->funcParam.size(); i++){
                        for(it = this->funcParam.at(i).begin(); it !=this->funcParam.at(i).end(); it++){
                            if(it->first == node->value){
                                Error(node->value +" is already defined as a parameter");
                            }
                        }
                    }
                    this->ident = node->value;
                    /*
                    if(this->st.isParam(this->funcName,this->funcType,node->value)){
                        Error("Identifier is already defined as a parameter");
                    }else{

                    }
                     //
                }else{
                    this->ident = node->value;
                }
            */
                //need to add to the current scope
            }
        }
    }
}

void InterpreterExecution::visit(ASTBinaryNode *node) {
    SymbolTable::primitive_type typeRhs = SymbolTable::primitive_type::n;
    SymbolTable::primitive_type typeLhs= SymbolTable::primitive_type::n;

    int currIValue;
    float currRValue;
    bool currBValue;
    std::string currSValue;


    if (node->lhs != nullptr) {
        node->lhs->Accept(this);
        typeLhs = this->Type;
        switch (typeLhs){
            case 0:
                currIValue = this->iValue;
                break;
            case 1:
                currRValue = this->rValue;
                break;
            case 2:
                currBValue = this->bValue;
                break;
            case 3:
                currSValue = this->sValue;
                break;
        }
    }



    if (node->rhs != nullptr){
        node->rhs->Accept(this);
        typeRhs = this->Type;


    }

    if(typeLhs != typeRhs){
        Error(typePrint(typeLhs) + " and " + typePrint(typeRhs) + " cannot be evaluated, since both are different type" );
    }else{
        this->Type = typeLhs;

        this->operation = node->operation;

        switch (this->Type){
            case 0:
                if(this->operation == "+"){
                    this->iValue = currIValue + this->iValue;
                }else if(this->operation == "-"){
                    this->iValue = currIValue - this->iValue;
                }else if(this->operation == "*"){
                    this->iValue = currIValue * this->iValue;
                }else if(this->operation == "/"){
                    this->iValue = currIValue / this->iValue;
                }
                break;
            case 1:
                if(this->operation == "+"){
                    this->rValue = currRValue + this->rValue;
                }else if(this->operation == "-"){
                    this->rValue = ((currRValue) - (this->rValue));
                }else if(this->operation == "*"){
                    this->rValue = currRValue * this->rValue;
                }else if(this->operation == "/"){
                    this->rValue = currRValue / this->rValue;
                }
                break;
            case 2:
                //if(this->operation == "not"){
                //    this->bValue = not (this->bValue);
                if(this->operation == "and"){
                    this->bValue = (currBValue) and (this->bValue);
                }else if(this->operation == "or"){
                    this->bValue = (currBValue) or (this->bValue);
                }/*else if(this->operation == ">"){
                    if(currBValue > this->bValue){

                    }
                }else if(this->operation == "<"){

                }else if(this->operation == "=="){

                }else if(this->operation == "!="){

                }else if(this->operation == "<="){

                }else if(this->operation == ">="){

                }
                */
                break;
            case 3:
                if(this->operation == "+") {
                    //this->sValue = (currSValue + this->sValue);
                    currSValue.erase(currSValue.size()-1);//removing the " from the 1st string
                    this->sValue.erase(0,1);//removing the " from the last string
                    this->sValue = currSValue+ this->sValue;
                }
                break;
        }
    }
 }

void InterpreterExecution::visit(ASTUnaryNode *node) {
    this->exists = true;
    node->lhs->Accept(this);
    if(node->operation == "not"){
        if (this->Type != 2) {//check for bool
            Error("Expression is not a Boolean, not operation invalid");
        }else{
            //get value of identifier and not it
            this->bValue = not this->bValue;
        }
    } else {// + /- case
        if (this->Type == 3) {//checking for string
            Error("Unary Expression - String cannot be added / subtracted");
        }else{
            //get value of identifier and not it
        }
    }
}

void InterpreterExecution::visit(ASTVariableDeclNode *node) {

    this->exists = false;
    typeSet(node->Type);
    SymbolTable::primitive_type identType = this->Type;

    node->Identifier->Accept(this);

    this->exists = true;
    node->Expr->Accept(this);

    if(this->st.inCurrentScope(this->ident)){
        Error("Variable is already defined in the current scope");
    }else if(this->st.isParam(this->funcName, this->funcType,this->ident)){
        Error("Variable is already defined in as a Parameter");
    }else{
        if(this->Type != identType){
            Error("Type of Identifier and Expression do not match");
        }else if(this->st.insertInScope(this->ident, this->Type)){
            std::cout << "Variable Added" << std::endl;
            std::cout <<"Contents of equation : " << valuePrint(this->Type) << std::endl;
            switch (this->Type){
                case 0:
                    this->st.setValue(this->ident,this->iValue);
                    break;
                case 1:
                    this->st.setValue(this->ident,this->rValue);
                    break;
                case 2:
                    this->st.setValue(this->ident,this->bValue);
                    break;
                case 3:
                    this->st.setValue(this->ident,this->sValue);
                    break;
            }
            //this->st.setValue(this->ident,this->iValue);
            //this->st.scopePrint();
        }else{
            Error("Variable was not added");
        }
    }
}

void InterpreterExecution::visit(ASTAssignmentNode *node) {
    this->exists = true;
    node->Identifier->Accept(this);
    std::string identifier = this->ident;
    if(this->st.inScope(this->ident)){
        SymbolTable::primitive_type varType = this->Type;
        this->exists = true;

        node->Expr->Accept(this);
        if(this->Type != varType){
            Error("Identifier "+  identifier +" of type " + typePrint(varType) + " and expression of type "+typePrint(this->Type) +" do not match");
        }else{
            //change the value of the symbol table
        }
    }else{
        if(this->st.isParam(this->funcName,this->funcType, this->ident)){
            SymbolTable::primitive_type varType = this->Type;
            this->exists = true;

            node->Expr->Accept(this);
            if(this->Type != varType){
                Error("Identifier "+  identifier +" of type " + typePrint(varType) + " and expression of type "+typePrint(this->Type) +" do not match");
            }else{
                //change the value of the symbol table
            }
        }else{
            Error("Identifier " + this->ident + " is not declared in the scope");
        }
    }
}

void InterpreterExecution::visit(ASTSubExpressionNode *node) {
    this->exists = true;
    node->Expr->Accept(this);
}

void InterpreterExecution::visit(ASTFunctionCallNode *node) {
    this->exists = true;
    node->Identifier->Accept(this);
    node->Parameters->Accept(this);
}

void InterpreterExecution::visit(ASTActualParametersNode *node) {
    this->exists = true;
    if(node->parameters.size() != this->funcParam.size()){
        Error("Number of Parameters given in the function call does not match the Number of Parameters in the Function Declaration");
    }else {
        for (int i = 0; i < node->parameters.size(); i++) {
            node->parameters.at(i)->Accept(this);

            std::map<std::string, SymbolTable::primitive_type>::iterator it;
            for (it = this->funcParam.at(i).begin(); it != this->funcParam.at(i).end(); it++) {
                if (this->Type != it->second) {

                    this->st.scopePrint();
                    Error("Parameter "+ std::to_string(i+1) +" has type " + typePrint(this->Type) + " and expecting the type " +  typePrint(it->second));
                }
            }
        }
    }
}

void InterpreterExecution::visit(ASTReturnNode *node) {
    this->exists = true;
    node->Expr->Accept(this);
    if(this->Type != this->funcType){
        Error("Return Statement of Type :" + typePrint(this->Type) + " does not match the function type :"+ typePrint(this->funcType));
    }
}

void InterpreterExecution::visit(ASTFunctionDeclNode *node) {
    this->exists = false;
    node->Identifier->Accept(this);
    this->funcName = this->ident;

    typeSet(node->Type);
    this->funcType = this->Type;

    node->Parameters->Accept(this);
    if(this->st.inCurrentScope(this->funcName)){
        if(this->st.getType(this->funcName) == this->funcType){
            Error("Function " + this->funcName +" is already defined with the same type " + typePrint(this->funcType));
        }
    }

    if(this->st.insertInScope(this->funcName,this->funcType, this->funcParam)){
        //std::cout<<"Insert Successful" << std::endl;
    }else{
        Error("Function was not added");
    }

    //std::cout << "Going to go into block " << std::endl;
    node->Block->Accept(this);


}

void InterpreterExecution::visit(ASTFormalParameterNode *node) {
    this->param = true;
    node->Identifier->Accept(this);

    typeSet(node->Type);

    std::map<std::string, SymbolTable::primitive_type >::iterator it;

    //checking if a parameter is already defined

    if(this->st.isParam(this->funcName,this->funcType, this->ident)){
        Error("Identifier " + this->ident + " is alreay defined as a parameter");
    }
    /*
    for(int j =0; j < this->funcParam.size(); j++){
        for(it = this->funcParam.at(j).begin(); it != this->funcParam.at(j).end(); it++){//should iterate only once
            if(this->ident == it->first){
                Error("Identifier " + this->ident + " is alreay defined as a parameter");
            }
        }
    }
*/
    this->para.insert(std::pair<std::string, SymbolTable::primitive_type>(this->ident,this->Type));
    this->param = false;
}

void InterpreterExecution::visit(ASTFormalParametersNode *node) {
    this->funcParam.clear();
    for(int i =0; i < node->parameters.size(); i++){
        this->para.clear();
        node->parameters.at(i)->Accept(this);
        this->funcParam.push_back(para);
    }
}

void InterpreterExecution::visit(ASTWriteNode *node) {
    this->exists = true;
    node->Expr->Accept(this);
}

void InterpreterExecution::visit(ASTIfStatementNode *node) {
    this->exists = true;
    node->Expression->Accept(this);
    if((this->operation == ">") || (this->operation == "<") || (this->operation == "==") || (this->operation == "!=") || (this->operation == "<=") || (this->operation == ">=")|| (this->operation == "and")|| (this->operation == "or")|| (this->operation == "not")){
        node->Block->Accept(this);
        node->ElseBlock->Accept(this);
    }else{
        Error("Operator " + this->operation + " is not allowed in if statement, expecting a relation Operation");
    }
}

void InterpreterExecution::visit(ASTWhileNode *node) {
    this->exists = true;
    node->Expr->Accept(this);
    if((this->operation == ">") || (this->operation == "<") || (this->operation == "==") || (this->operation == "!=") || (this->operation == "<=") || (this->operation == ">=")||(this->operation == "and")||(this->operation == "or")|| (this->operation == "not")){
        node->Block->Accept(this);
    }else{
        Error("Operator " + this->operation + " is not allowed in while loop, expecting a relation Operation");
    }
}

void InterpreterExecution::visit(ASTBlockNode *node) {

    if(this->st.createScope()){
        //std::cout << "Creating an inner scope" << std::endl;
        int j = node->statements.size();

        for(int k =0; k < j; k++){
            node->statements.at(k)->Accept(this);
        }
        this->st.scopePrint();
        if(this->st.deleteScope()){
            //std::cout << "Block Scope Deleted" << std::endl;
        }else{
            Error("Could not delete Scope");
        }
    }else{
        Error("Error creating Block Scope");

    }

}

