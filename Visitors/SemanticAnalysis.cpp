#include "SemanticAnalysis.h"

SemanticAnalysis::SemanticAnalysis() {

}

void SemanticAnalysis::typeSet(std::string type) {
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

std::string SemanticAnalysis::typePrint(SymbolTable::primitive_type type) {
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

void SemanticAnalysis::Error(std::string error) {
    std::cerr << "Semantic Error : " << error << std::endl;
    exit(1);
}

void SemanticAnalysis::visit(ASTNode *node) {}

void SemanticAnalysis::visit(ASTExpressionNode *node) {}

void SemanticAnalysis::visit(ASTStatementNode *node) {}

void SemanticAnalysis::visit(ASTProgramNode *node) {
    this->st = SymbolTable();

    this->Type = SymbolTable::primitive_type::n;
    this->funcType = SymbolTable::primitive_type::n;
    this->retType = SymbolTable::primitive_type::n;

    this->ident = "";
    this->operation = "";
    this->funcName = "";

    this->exists = false;

/*    this->add = false;
    this->ret = false;
    this->func = false;
    this->param = false;
*/
    this->funcParam.clear();
    this->para.clear();

    if(this->st.createScope() == true){
        std::cout << "Global Scope created" << std::endl;
        int j = node->statements.size();

        for(int i =0; i < j; i++){
            std::cout << i+1 <<std::endl;
            this->st.scopePrint();
            node->statements.at(i)->Accept(this);
        }

        this->st.scopePrint();

        if(this->st.deleteScope() == true){
            std::cout << "Global Scope Deleted" << std::endl;
        }else{
            Error("Could not delete Scope");
        }
    }else{
        Error("Error creating Global Scope");

    }
}

void SemanticAnalysis::visit(ASTIntegerNode *node) {
    typeSet("int");
}

void SemanticAnalysis::visit(ASTFloatNode *node) {
    typeSet("real");
}

void SemanticAnalysis::visit(ASTBoolNode *node) {
    typeSet("bool");
}

void SemanticAnalysis::visit(ASTStringNode *node) {
    typeSet("string");
}

void SemanticAnalysis::visit(ASTIdentifierNode *node) {
    //this->ident = node->value;

    if(this->param){
        //not to be done here but in param
        //if(this->st.isParam(this->funcName, this->funcType, node->value)){
        //    Error(node->value+ " is already defined in the function " + this->funcName);
        //}else{
            this->ident = node->value;
        //}
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

void SemanticAnalysis::visit(ASTBinaryNode *node) {
    SymbolTable::primitive_type typeRhs = SymbolTable::primitive_type::n;
    SymbolTable::primitive_type typeLhs= SymbolTable::primitive_type::n;

    if (node->lhs != nullptr) {
        node->lhs->Accept(this);
        typeLhs = this->Type;
    }

    if (node->rhs != nullptr){
        node->rhs->Accept(this);
        typeRhs = this->Type;
    }

    std::cout << "Lhs : " <<  typePrint(typeLhs) << " Rhs : " <<  typePrint(typeRhs) << std::endl;

    if(typeLhs != typeRhs){
        Error(typePrint(typeLhs) + " and " + typePrint(typeRhs) + " cannot be evaluated, since both are different type" );
    }else{
        this->Type = typeLhs;
    }
    this->operation = node->operation;
}

void SemanticAnalysis::visit(ASTUnaryNode *node) {
    node->lhs->Accept(this);
    if(node->operation == "not"){
        if (this->Type != 2) {//check for bool
            Error("Expression is not a Boolean, not operation invalid");
        }
    } else {// + /- case
        if (this->Type == 3) {//checking for string
            Error("Unary Expression - String cannot be added / subtracted");
        }
    }
}

void SemanticAnalysis::visit(ASTVariableDeclNode *node) {

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
            //std::cout << "Variable Added" << std::endl;
            //this->st.scopePrint();
        }else{
            Error("Variable was not added");
        }
    }
}

void SemanticAnalysis::visit(ASTAssignmentNode *node) {
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

void SemanticAnalysis::visit(ASTSubExpressionNode *node) {
    this->exists = true;
    node->Expr->Accept(this);
}

void SemanticAnalysis::visit(ASTFunctionCallNode *node) {
    this->exists = true;
    node->Identifier->Accept(this);
    node->Parameters->Accept(this);
}

void SemanticAnalysis::visit(ASTActualParametersNode *node) {
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

void SemanticAnalysis::visit(ASTReturnNode *node) {
    node->Expr->Accept(this);
    if(this->Type != this->funcType){
        Error("Return Statement of Type :" + typePrint(this->Type) + " does not match the function type :"+ typePrint(this->funcType));
    }
}

void SemanticAnalysis::visit(ASTFunctionDeclNode *node) {
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

void SemanticAnalysis::visit(ASTFormalParameterNode *node) {
    this->param = true;
    node->Identifier->Accept(this);
    typeSet(node->Type);
    std::map<std::string, SymbolTable::primitive_type >::iterator it;

    //checking if a parameter is already defined
    for(int j =0; j < this->funcParam.size(); j++){
        for(it = this->funcParam.at(j).begin(); it != this->funcParam.at(j).end(); it++){//should iterate only once
            if(this->ident == it->first){
                Error("Identifier " + this->ident + " is alreay defined as a parameter");
            }
        }
    }

    this->para.insert(std::pair<std::string, SymbolTable::primitive_type>(this->ident,this->Type));
    this->param = false;
}

void SemanticAnalysis::visit(ASTFormalParametersNode *node) {
    this->funcParam.clear();
    for(int i =0; i < node->parameters.size(); i++){
        this->para.clear();
        node->parameters.at(i)->Accept(this);
        this->funcParam.push_back(para);
    }
}

void SemanticAnalysis::visit(ASTWriteNode *node) {
    this->exists = true;
    node->Expr->Accept(this);
}

void SemanticAnalysis::visit(ASTIfStatementNode *node) {
    node->Expression->Accept(this);
    if((this->operation == ">") || (this->operation == "<") || (this->operation == "==") || (this->operation == "!=") || (this->operation == "<=") || (this->operation == ">=")|| (this->operation == "and")|| (this->operation == "or")|| (this->operation == "not")){
        node->Block->Accept(this);
        node->ElseBlock->Accept(this);
    }else{
        Error("Operator " + this->operation + " is not allowed in if statement, expecting a relation Operation");
    }
}

void SemanticAnalysis::visit(ASTWhileNode *node) {
    node->Expr->Accept(this);
    if((this->operation == ">") || (this->operation == "<") || (this->operation == "==") || (this->operation == "!=") || (this->operation == "<=") || (this->operation == ">=")||(this->operation == "and")||(this->operation == "or")|| (this->operation == "not")){
        node->Block->Accept(this);
    }else{
        Error("Operator " + this->operation + " is not allowed in while loop, expecting a relation Operation");
    }
}

void SemanticAnalysis::visit(ASTBlockNode *node) {

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


