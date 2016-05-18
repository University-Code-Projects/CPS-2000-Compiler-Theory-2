//
// Created by cps200x on 5/7/16.
//

#include "Parser.h"

Parser::Parser(Lexer &pLexer) : lex(pLexer){
    //std::cout << "Entry in Parser Constructor" << std::endl;
}

ASTNode * Parser::Parse(){
    //std::cout<< "Parser Entry" << std::endl;

    ASTProgramNode *rootNode = new ASTProgramNode();

    ASTStatementNode * statement = nullptr;

    CurrToken = lex.getNextToken();

    while((CurrToken.token_type != Lexer::TOK_eof)&&(CurrToken.token_type != Lexer::TOK_error)){
        //std::cout << "Going into state"<< CurrToken.toString() << std::endl;
        statement = ParseStatement();
        //std::cout <<"Coming from state" << CurrToken.toString() << std::endl;

        //save to the root node as a child
        //CurrToken = lex.getNextToken();
        if(statement != nullptr) {
            rootNode->addStatement(statement);
        }
        //statement->Accept(v);

    }
    //std::cout << "Printing All the Statements" << std::endl;
    //rootNode->Accept(v);
    //std::cout<< "Final Token : "<< CurrToken.toString() << std::endl;
    //std::cout << "Returning Node" << std::endl;
    return rootNode;
}


ASTNode *Parser::ParseRepl() {
    ASTNode * repl = nullptr;
    if(CurrToken.token_type == Lexer::TOK_comment){
        CurrToken = lex.getNextToken();
        return repl;
    }
    //std::cout << CurrToken.toString() << std::endl;
    switch (CurrToken.token_type){
        case Lexer::TOK_var:
            //std::cout<< "Variable Decleration"  << std::endl;
            repl = ParseVariableDecl();
            break;
        case Lexer::TOK_set:
            //std::cerr<< "Variable Assignment"  << std::endl;
            repl = ParseAssignment();
            //std::cerr << "Return from statement" << std::endl;
            //std::cerr << CurrToken.toString() << std::endl;

            break;
        case Lexer::TOK_write:
            //std::cout<< "Write Statement"  << std::endl;
            repl = ParseWriteStatement();
            break;
        case Lexer::TOK_return:
            //std::cout<< "Return Statement"  << std::endl;
            repl = ParseReturnStatement();
            break;
        case Lexer::TOK_def:
            //std::cout<< "Function Decleration"  << std::endl;
            repl = ParseFunctionDecl();
            break;
        case Lexer::TOK_if:
            //std::cout<< "If Statement"  << std::endl;
            repl = ParseIfStatement();
            break;
        case Lexer::TOK_while:
            //std::cout<< "While Statement"  << std::endl;
            repl = ParseWhileStatement();
            break;

        case Lexer::TOK_punc:
            if(CurrToken.id == "{") {
                //std::cout << "Block Statement" << std::endl;
                repl = ParseBlock();
            }
            break;
        case Lexer::TOK_integer:
            repl = ParseExpression();
            break;

        case Lexer::TOK_realInt:
            repl = ParseExpression();
            break;
        case Lexer::TOK_unary:
            repl = ParseUnary();
            break;

        case Lexer::TOK_identifier:
            repl = ParseExpression();
            break;
        case Lexer::TOK_string:
            repl = ParseExpression();
            break;
        case Lexer::TOK_bool:
            repl = ParseExpression();
            break;
        default:
            //std::cout << CurrToken.toString() << std::endl;
            Error("No statement found");
            break;
    }

    return repl;
}

ASTStatementNode * Parser::ParseStatement(){

    ASTStatementNode * statement = nullptr;
    //std::cout << "Entry in Parse Statement" << std::endl;
    //std::cout << CurrToken.toString() << std::endl;

    if(CurrToken.token_type == Lexer::TOK_comment){
        CurrToken = lex.getNextToken();
        return statement;
    }
    //std::cout << CurrToken.toString() << std::endl;
    switch (CurrToken.token_type){
        case Lexer::TOK_var:
            //std::cout<< "Variable Decleration"  << std::endl;
            statement = ParseVariableDecl();
            break;
        case Lexer::TOK_set:
            //std::cerr<< "Variable Assignment"  << std::endl;
            statement = ParseAssignment();
        //std::cerr << "Return from statement" << std::endl;
            //std::cerr << CurrToken.toString() << std::endl;

            break;
        case Lexer::TOK_write:
            //std::cout<< "Write Statement"  << std::endl;
            statement = ParseWriteStatement();
            break;
        case Lexer::TOK_return:
            //std::cout<< "Return Statement"  << std::endl;
            statement = ParseReturnStatement();
            break;
        case Lexer::TOK_def:
            //std::cout<< "Function Decleration"  << std::endl;
            statement = ParseFunctionDecl();
            break;
        case Lexer::TOK_if:
            //std::cout<< "If Statement"  << std::endl;
            statement = ParseIfStatement();
            break;
        case Lexer::TOK_while:
            //std::cout<< "While Statement"  << std::endl;
            statement = ParseWhileStatement();
            break;

        case Lexer::TOK_punc:
            if(CurrToken.id == "{") {
                //std::cout << "Block Statement" << std::endl;
                statement = ParseBlock();
            }
            break;
        default:
            //std::cout << CurrToken.toString() << std::endl;
            Error("No statement found");
            break;
    }

    //std::cout << CurrToken.toString() << std::endl;
    return statement;
}

void * Parser::Error(const char *str){
    std::cerr << "Syntax Error : " << str << std::endl;
    exit(1);
}

ASTStatementNode * Parser::ParseVariableDecl(){
    //std::cout << "Entry in Parse Variable Declaration" << std::endl;

    ASTExpressionNode * identifier = nullptr;
    ASTExpressionNode * expr = nullptr;
    ASTVariableDeclNode * declartion = nullptr;
    //consuming current token;
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_identifier){
        Error("Identifier was not found in Variable Declaration");
    }else{
        identifier = ParseIdentifier();
        //afterwards link the the ASTStatementNode
    }
    CurrToken = lex.getNextToken();
    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("':' was not found in Variable Declaration");
    }

    //consuming the ':'
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_type){
        Error("Identifier TYPE was not found in Variable Declaration");
    }
    std::string type = CurrToken.id;

    CurrToken = lex.getNextToken();
    //std::cout << CurrToken.toString() << std::endl;

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'=' was not found in Variable Declaration");
    }else{
        if(CurrToken.id[0] != '='){
            Error("'=' was not found in Variable Declaration");
        }else{
            //consuming the '='
            CurrToken = lex.getNextToken();
            //std::cout << CurrToken.toString() << std::endl;
            expr = ParseExpression();
            //std::cout << CurrToken.toString() << std::endl;
        }
    }

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found");
    }else{
        if(CurrToken.id == ";"){
            //save the variable declartaion to the program node

            //consume the ';'
            declartion = new ASTVariableDeclNode(identifier,expr,type);
            CurrToken = lex.getNextToken();

        }else{
            Error("';' was not found");
        }

    }
    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    return declartion;
}

ASTStatementNode * Parser::ParseAssignment(){

    //std::cout << "Entry in Parse Assignment" << std::endl;
    //std::string statement = CurrToken.id;

    ASTAssignmentNode * statement = nullptr;
    ASTExpressionNode * identifier = nullptr;
    ASTExpressionNode * expr = nullptr;

    //consuming current token;
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_identifier){
        Error("Identifier was not found in Variable Assignment");
    }else{
        identifier = ParseIdentifier();
        //afterwards link the the ASTStatementNode
    }

    CurrToken = lex.getNextToken();
    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'=' was not found in Variable Assignment");
    }else{
        if(CurrToken.id[0] != '='){
            Error("'=' was not found in Variable Assignment");
        }else{
            CurrToken = lex.getNextToken();
            expr = ParseExpression();
            //afterwards link the the ASTStatementNode
        }
    }

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found in Assignment");
    }else{
        if(CurrToken.id == ";"){
            //save the variable declartaion to the program node
            //consume the ';'
            statement = new ASTAssignmentNode(identifier,expr);
            CurrToken = lex.getNextToken();
        }else{
            Error("';' was not found in Assignment");
        }

    }
    //std::cout << CurrToken.toString() << std::endl;
    //std::cerr << "Assingment Return " << std::endl;
    return statement;
}

ASTStatementNode * Parser::ParseWriteStatement(){
    //std::cout << "Entry in Parse Write" << std::endl;

    ASTWriteNode * statement = nullptr;

    //consuming current token which is the write token;
    CurrToken = lex.getNextToken();

    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    ASTExpressionNode * expr = ParseExpression();


    //SOMETHING HEERE IS HAPPENEING AND DUNNO WHAT
    //CurrToken.toString();


    //std::cerr<< "Current Token : "<< CurrToken.toString() << std::endl;

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found in Write");
    }else{
        if(CurrToken.id[0] == ';'){
            //consume the ';'
            CurrToken = lex.getNextToken();
            statement = new ASTWriteNode(expr);

        }else{
            Error("';' was not found in Write");
        }
    }
    //std::cout << "Returning Statement" << std::endl;
    return statement;
}

ASTStatementNode * Parser::ParseReturnStatement() {
    //std::cout << "Entry in Parse Return" << std::endl;
    ASTReturnNode * statement = nullptr;

    //consuming the token return
    CurrToken = lex.getNextToken();
    ASTExpressionNode * expr = ParseExpression();

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found in Return");
    }else{
        if(CurrToken.id != ";"){
            Error("';' was not found in Return");
        }else{
            CurrToken = lex.getNextToken();
            statement = new ASTReturnNode(expr);
        }
    }
    return statement;
}

ASTStatementNode * Parser::ParseFunctionDecl(){
    //std::cout << "Entry in Parse Function Declaration" << std::endl;
    //ASTStatementNode * statement = nullptr;

    ASTFunctionDeclNode * functionDecl = nullptr;
    ASTExpressionNode * identifier = nullptr;
    ASTFormalParametersNode * params = nullptr;


    //consuming current token;
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_identifier){
        Error("Identifier was not found in Function Declaration");
    }else{
        identifier = ParseIdentifier();
        //afterwards link the the ASTStatementNode
    }
    CurrToken = lex.getNextToken();
    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'(' was not found in Function Declaration");
    }else{
        if(CurrToken.id != "("){
            Error("'(' was not found in Function Declaration");
        }else{
            CurrToken = lex.getNextToken();
            params = ParseFormalParams();
            if(CurrToken.token_type != Lexer::TOK_punc){
                Error("')' was not found in Function Declaration of the parameters");
            }else {
                if (CurrToken.id != ")") {
                    Error("')' was not found in Function Declaration of the parameters");
                } else {
                    CurrToken = lex.getNextToken();//consuming the ')'
                }
            }
        }
    }

    //ASTFormalParametersNode * params = ParseFormalParams();

    //CurrToken = lex.getNextToken();
    //std::cout<< ">>>Current Token : "<< CurrToken.toString() << std::endl;
//being done in previous else statement
/*
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("Formal Parameters were set incorrectly as no ')' was found");
    }else{
        if(CurrToken.id != ")"){
            Error("Formal Parameters were set incorrectly as no ')' was found");
        }
    }
  */
    //consuming the )
    //CurrToken = lex.getNextToken();
    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("':' was not found in Function Declaration");
    }else{
        if(CurrToken.id != ":"){
            Error("':' was not found in Function Declaration");
        }else{
            CurrToken = lex.getNextToken();
        }
    }

    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    std::string type = CurrToken.id;

    //consuming the type
    CurrToken = lex.getNextToken();
    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    //link block to statment
    ASTStatementNode * block = ParseBlock();

    functionDecl = new ASTFunctionDeclNode(identifier,params,type,block);
    return functionDecl;
}

ASTStatementNode * Parser::ParseIfStatement(){

    //std::cout << "Entry in Parse If Statement" << std::endl;
    //std::string statement = CurrToken.id;
    ASTIfStatementNode * statement = nullptr;
    ASTExpressionNode * expr = nullptr;
    ASTStatementNode * block = nullptr;

    //consuming current token if;
    CurrToken = lex.getNextToken();

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'(' was not found in If Statement");
    }else{
        if(CurrToken.id != "("){
            Error("'(' was not found in If Statement");
        }else{
            CurrToken = lex.getNextToken();
            expr = ParseExpression();
            //afterwards link the the ASTStatementNode
        }
    }

    //std::cout << CurrToken.toString() << std::endl;
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("')' was not found in If Statement");
    }else{
        if(CurrToken.id != ")"){
            Error("')' was not found in If Statement");
        }else{
            CurrToken = lex.getNextToken();
        }
    }

    //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
    //link block to statement
    block = ParseBlock();
    //Cu
    if(CurrToken.token_type != Lexer::TOK_if){
        statement = new ASTIfStatementNode(expr,block,nullptr);
    }else{
        if(CurrToken.id != "else"){
            Error("'else' was not found in If Statement but if was found");
        }else{
            //consuming else
            CurrToken = lex.getNextToken();
            //std::cout<< "Current Token : "<< CurrToken.toString() << std::endl;
            //link block to statement
            ASTStatementNode * blockElse = ParseBlock();
            statement = new ASTIfStatementNode(expr,block,blockElse);
        }
    }
    return statement;
}

ASTStatementNode * Parser::ParseWhileStatement(){
    //std::cout << "Entry in Parse While Statement" << std::endl;
    ASTWhileNode * statement = nullptr;
    ASTExpressionNode * expr = nullptr;
    ASTStatementNode * block = nullptr;

    //consuming current while token;
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'(' was not found in While Statement");
    }else{
        if(CurrToken.id != "("){
            Error("'(' was not found in While Statement");
        }else{
            //consuming the '('
            CurrToken = lex.getNextToken();
            expr = ParseExpression();
            //std::cout << CurrToken.toString() << std::endl;
            //afterwards link the the ASTStatementNode
            if(CurrToken.token_type != Lexer::TOK_punc){
                Error("')' was not found after Expression");
            }else{
                if(CurrToken.id != ")") {
                    Error("')' was not found after Expression");
                }else{
                    CurrToken = lex.getNextToken();
                    //link block to the statement
                    block = ParseBlock();
                }
            }
        }
    }
    statement = new ASTWhileNode(expr,block);
    return statement;
}

ASTStatementNode * Parser::ParseBlock(){
    //std::cout << "Entry in Parse Block" << std::endl;
    ASTBlockNode * block = new ASTBlockNode();
    ASTStatementNode * statement = nullptr;

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'{' was not found in Block");
    }else{
        if(CurrToken.id != "{"){
            Error("'{' was not found in Block");
        }else{
            //consuming the '{'
            CurrToken = lex.getNextToken();
        }
    }

    statement = ParseStatement();
    if(statement != nullptr) {
        block->addStatement(statement);
    }

    while(CurrToken.id[0] != '}') {
        statement = ParseStatement();
        if (statement != nullptr) {
            block->addStatement(statement);
        }
    }


    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'}' was not found in Block");
    }else{
        if(CurrToken.id != "}"){
            Error("'}' was not found in Block");
        }else{
            //consuming the '}'
            CurrToken = lex.getNextToken();
        }
    }
    return block;
}

ASTExpressionNode * Parser::ParseIdentifier(){
    //std::cout << "Entry in Parse Identifier" << std::endl;
    //save it as a new Identifier
    ASTIdentifierNode * identifier = new ASTIdentifierNode(CurrToken.id);
    return identifier;
}

ASTExpressionNode * Parser::ParseExpression(){
    //std::cout << "Entry in Parse Expression" << std::endl;

    //save it as a new expr
    ASTExpressionNode * simpleExpr = ParseSimpleExpression();

    while(CurrToken.token_type == Lexer::TOK_realationOp){
        //std::cout << "Add Op found next" << std::endl;
        ASTExpressionNode * binOp = ParseBinaryOperation(2, simpleExpr);
        simpleExpr = binOp;
        //std::cout << CurrToken.toString() << std::endl;
    }

    return simpleExpr;
}

ASTExpressionNode * Parser::ParseSimpleExpression(){
    //std::cout << "Entry in Parse Simple Expression" << std::endl;
    //save it as a new SimpleExpr
    ASTExpressionNode * term = ParseTerm();

    //std::cout << CurrToken.toString() << std::endl;
    while(CurrToken.token_type == Lexer::TOK_addOp){
        //std::cout << "Add Op found next" << std::endl;
        ASTExpressionNode * binOp = ParseBinaryOperation(1, term);
        term = binOp;
        //std::cout << CurrToken.toString() << std::endl;
    }
    return term;
}

ASTExpressionNode * Parser::ParseTerm(){
    //std::cout << "Entry in Parse Term" << std::endl;
    //save it as a new Term
    ASTExpressionNode * lhs = ParseFactor();

    //std::cout << "RETURN FROM FACTOR" << std::endl;

    //XMLPrint * v = new XMLPrint();
    //lhs->Accept(v);
    //std::cerr << CurrToken.toString() << std::endl;
    while(CurrToken.token_type == Lexer::TOK_multOp){

        //std::cout << "Mult Op found next" << std::endl;
        ASTExpressionNode * binOp = ParseBinaryOperation(0, lhs);
        lhs = binOp;
        //std::cout << CurrToken.toString() << std::endl;
    }
    return lhs;
}

ASTExpressionNode * Parser::ParseFactor(){
    //std::cout << "Entry in Parse Factor" << std::endl;
    //std::cout << CurrToken.toString() << std::endl;

    ASTExpressionNode * ans = nullptr;

    switch (CurrToken.token_type) {
        case Lexer::TOK_bool: {
            bool result;
            if (CurrToken.id == "true") {
                result = true;
            } else {
                result = false;
            }
            ans = new ASTBoolNode(result);
            break;
        }
        case Lexer::TOK_integer: {
            //have to type cast from float to int as token.num is a float
            ans = new ASTIntegerNode((int)CurrToken.num);//new integer node
            break;
        }
        case Lexer::TOK_realInt:{
            ans = new ASTFloatNode(CurrToken.num);//new float node
            break;
        }
        case Lexer::TOK_string: {
            ans = new ASTStringNode(CurrToken.id);//new string node
            break;
        }

        case Lexer::TOK_identifier: {
            ASTExpressionNode * id = ParseIdentifier();


            Lexer::Token peek = lex.tokenPeek();
            if(peek.id == "("){//function call found


                //consuming the Identifier
                ASTIdentifierNode * ident = new ASTIdentifierNode(CurrToken.id);
                CurrToken = lex.getNextToken();
                //consuming the '('
                CurrToken = lex.getNextToken();//getting the equation

                ASTActualParametersNode * params = ParseActualParams();

                //ParseSubExpression();

                //std::cerr << "Checking after parsee actual param" << std::endl;
                //std::cerr << CurrToken.toString() << std::endl;

                if(CurrToken.token_type != Lexer::TOK_punc){
                    Error("')' was not found in Function Call");
                }else{
                    if(CurrToken.id != ")"){
                        Error("')' was not found in Function Call");
                    }
                }

                ASTFunctionCallNode * funcCall = new ASTFunctionCallNode(ident,params);

                ans = funcCall;

                //std::cerr << "Function Call" <<CurrToken.toString() << std::endl;
                /*
                if(CurrToken.id[0] == ')'){
                    ASTExpressionNode * param = nullptr;
                }else{

                    if(funcDecl) {
                        ASTExpressionNode *param = ParseActualParams();
                        CurrToken = lex.getNextToken();//getting the ')'
                        if (CurrToken.id != ")") {
                            Error("')' was not found at end of Parameters");
                        } else {
                            ans = param;
                        }
                    }else{
                        ASTExpressionNode *param = ParseActualParams();
                        CurrToken = lex.getNextToken();//getting the ')'
                        if (CurrToken.id != ")") {
                            Error("')' was not found at end of Parameters");
                        } else {
                            ans = param;
                        }
                    }
                }
                */
            }else{//identifier found
                ans = id;
            }
            break;
        }


        case Lexer::TOK_punc: {
            if (CurrToken.id == "(") {
                CurrToken = lex.getNextToken();


                ASTExpressionNode *expr = ParseExpression();
                ASTSubExpressionNode *subExpr = new ASTSubExpressionNode(expr);

                if (CurrToken.id != ")") {
                    Error("')' was not found at the end of the expression in Sub Expression Creation");
                }
                ans = subExpr;//new sub expression node
            } /*else if(CurrToken.id == ")"){


                //NO PARAMETERS FOUND HENCE RETURN NULL

                //return ans;
            }*/
            else{
                Error("Token is of the incorrect format");
            }
            break;
        }

        case Lexer::TOK_unary: {
            //std::string symbol = CurrToken.id;
            ASTUnaryNode * unary = ParseUnary();
            //XMLPrint * v = new XMLPrint();
            //unary->Accept(v);
            return unary;
            //unary = ans;
            //ASTExpressionNode * unary = ParseExpression();
            //ans = new ASTBinaryNode(symbol,unary, nullptr);
            //ans = ParseBinaryOperation(1,unary);
            //ans = symbol+unary;

            //return ans;
            break;
        }
        case Lexer::TOK_addOp:{
            if(CurrToken.id == "or"){
                Error("'or' found when '+'/ '-' was expected");
            }
            //std::string symbol = CurrToken.id;
            //CurrToken=lex.getNextToken();
            //ASTExpressionNode * unary = ParseExpression();
            //ans = new ASTBinaryNode(symbol, unary, nullptr);
            //ans = ParseBinaryOperation(1,unary);
            //ans = symbol+unary;
            ASTExpressionNode * unary = ParseUnary();
            return unary;
            unary = ans;
            //XMLPrint * v = new XMLPrint();
            //unary->Accept(v);
            return ans;
        }
        default:{
            Error("Token was not recognised in Parse Factor");
        }
    }

    //consuming the factor
    CurrToken = lex.getNextToken();
    //std::cout << CurrToken.toString() << std::endl;
    return ans;
}
/*
ASTExpressionNode *Parser::ParseActualParam() {

    ASTExpressionNode * params = nullptr;
    ASTExpressionNode * ident = ParseIdentifier();
    CurrToken = lex.getNextToken();
    if(CurrToken.id != ":"){
        Error("Formal Parameters are set incorrectly, ':' was not found");
    }
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_type){
        Error("Formal Parameters are set incorrect the type was not found");
    }
    params = new ASTFormalParameterNode(ident, CurrToken.id);
    //consuming the type
    CurrToken = lex.getNextToken();
    return params;


    return nullptr;
}
*/
ASTActualParametersNode * Parser::ParseActualParams(){
    //std::cout << "Entry in Parse Actual Params" << std::endl;

    ASTActualParametersNode * actualParameter = new ASTActualParametersNode();
    if(CurrToken.id == ")"){
        return actualParameter;
    }else {
        ASTExpressionNode *params = ParseExpression();

        actualParameter->addParameter(params);

        while (CurrToken.id[0] == ',') {
            //consuming the ','
            CurrToken = lex.getNextToken();
            params = ParseExpression();
            actualParameter->addParameter(params);
        }
        return actualParameter;

    }
/*

    ASTExpressionNode * params = ParseExpression();

    if(lex.tokenPeek().id == ","){
        CurrToken = lex.getNextToken();//getting the ','
        CurrToken = lex.getNextToken();//getting the expression
        params = ParseActualParams();
    }else{
        return params;
    }
  */
}

ASTExpressionNode * Parser::ParseBinaryOperation(int prec, ASTExpressionNode * lhs){
    //std::cout << "Entry in Binary Operation " <<std::endl;
    //std::cout << CurrToken.toString() <<std::endl;

    //link currToken (operation) to lhs then do the switch statement
    std::string operation = CurrToken.id;
    CurrToken = lex.getNextToken();
    //std::cout << CurrToken.toString() <<std::endl;
    ASTExpressionNode * rhs;
    switch (prec){
        case 0:{//multOp
            rhs = ParseFactor();
            break;
        }
        case 1:{//addOp
            rhs = ParseTerm();
            break;
        }
        case 2:{//relOp
            rhs = ParseSimpleExpression();
            break;
        }
        default:
            Error("Precedence level is incorrectly given by parser");
    }

    //link operation to the rhs that was just generated
    //return the highest operation node of the tree
    ASTExpressionNode * result = new ASTBinaryNode(operation,lhs,rhs);//uncertain about this line
    return result;
}

ASTExpressionNode * Parser::ParseFormalParam() {
    //std::cout << "Entry in Parse Formal Param" << std::endl;
    //std::cout << CurrToken.toString() << std::endl;
    ASTExpressionNode * params = nullptr;
    ASTExpressionNode * ident = ParseIdentifier();
    CurrToken = lex.getNextToken();
    if(CurrToken.id != ":"){
        Error("Formal Parameters are set incorrectly, ':' was not found");
    }
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_type){
        Error("Formal Parameters are set incorrect the type was not found");
    }
    params = new ASTFormalParameterNode(ident, CurrToken.id);
    //consuming the type
   CurrToken = lex.getNextToken();
    return params;
}

ASTFormalParametersNode * Parser::ParseFormalParams() {
    //std::cout << "Entry in Parse Formal Params" << std::endl;
    //std::cout << CurrToken.toString() << std::endl;
    //ASTExpressionNode * formalParams = new ASTFormalParametersNode();
    ASTFormalParametersNode * formalParameter = new ASTFormalParametersNode();
    ASTExpressionNode * params = ParseFormalParam();

    formalParameter->addParameter(params);

    while(CurrToken.id[0] == ','){
        CurrToken = lex.getNextToken();
        params = ParseFormalParam();
        formalParameter->addParameter(params);
    }
    return formalParameter;
}

ASTUnaryNode *Parser::ParseUnary() {
    //std::cerr << "entry in parse" << std::endl;
    std::string symbol = CurrToken.id;
    //consuming the unary token
    CurrToken = lex.getNextToken();

    ASTExpressionNode * expr = ParseExpression();

    //ASTUnaryNode *unary = new ASTUnaryNode(symbol,expr);
    ASTUnaryNode * unary = new ASTUnaryNode(symbol,expr);

    //std::cout << "FROM PARSE UNARY" << std::endl;
    //XMLPrint * v = new XMLPrint();
    //unary->Accept(v);
    return unary;
}
