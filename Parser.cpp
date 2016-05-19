//
// Created by cps200x on 5/7/16.
//

#include "Parser.h"

Parser::Parser(bool text,Lexer &pLexer) : lex(text,pLexer){}

void * Parser::Error(const char *str){
    std::cerr << "Syntax Error : " << str << std::endl;
    exit(1);
}

ASTNode * Parser::Parse(){

    ASTProgramNode *rootNode = new ASTProgramNode();
    ASTStatementNode * statement = nullptr;

    //getting the 1st token
    CurrToken = lex.getNextToken();

    while((CurrToken.token_type != Lexer::TOK_eof)&&(CurrToken.token_type != Lexer::TOK_error)){
        //get the correct statement from ParseStatement();
        statement = ParseStatement();
        //save to the root node as a child if it is not a nullptr
        if(statement != nullptr) {
            rootNode->addStatement(statement);
        }else{
            //tok error found
            break;
        }
    }
    return rootNode;
}

ASTNode *Parser::ParseRepl() {
    ASTProgramNode *rootNode = new ASTProgramNode();
    ASTStatementNode * statement = nullptr;

    CurrToken = lex.getNextToken();

    while((CurrToken.token_type != Lexer::TOK_eof)&&(CurrToken.token_type != Lexer::TOK_error)){
        statement = ParseStatement();
        //save to the root node as a child
        if(statement != nullptr) {
            rootNode->addStatement(statement);
        }else{
            //check for expression
            ASTNode * repl = nullptr;
            switch (CurrToken.token_type){
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
                case Lexer::TOK_punc:
                    if(CurrToken.id == "("){
                        repl = ParseSimpleExpression();
                    }
                    break;
            }
            return repl;
        }
    }
    return rootNode;
}

ASTStatementNode * Parser::ParseStatement(){
    //going to check what type of expression the token holds
    //initialise it as a null pointer
    ASTStatementNode * statement = nullptr;
    //cannot parse a comment thus return a null pointer
    if(CurrToken.token_type == Lexer::TOK_comment){
        CurrToken = lex.getNextToken();
        return statement;
    }

    switch (CurrToken.token_type){
        case Lexer::TOK_var:
            //Variable Declaration
            statement = ParseVariableDecl();
            break;
        case Lexer::TOK_set:
            //Variable Assignment
            statement = ParseAssignment();
            break;
        case Lexer::TOK_write:
            //Write Statement
            statement = ParseWriteStatement();
            break;
        case Lexer::TOK_return:
            //Return Statement
            statement = ParseReturnStatement();
            break;
        case Lexer::TOK_def:
            //Function Declaration
            statement = ParseFunctionDecl();
            break;
        case Lexer::TOK_if:
            //If Statement
            statement = ParseIfStatement();
            break;
        case Lexer::TOK_while:
            //While Statement
            statement = ParseWhileStatement();
            break;

        case Lexer::TOK_punc:
            if(CurrToken.id == "{") {
                //Block Statement
                statement = ParseBlock();
            }
            break;

        default:
            //std::cerr << "No statement found" << std::endl;
            //Error("No statement found");
            break;
    }
    return statement;
}

ASTStatementNode * Parser::ParseVariableDecl(){
    //declaration of nodes
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

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("':' was not found in Variable Declaration");
    }

    //consuming the ':'
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_type){
        Error("Identifier TYPE was not found in Variable Declaration");
    }

    std::string type = CurrToken.id;

    //consuming the identifier
    CurrToken = lex.getNextToken();

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'=' was not found in Variable Declaration");
    }else{
        if(CurrToken.id[0] != '='){
            Error("'=' was not found in Variable Declaration");
        }else{
            //consuming the '='
            CurrToken = lex.getNextToken();
            expr = ParseExpression();
        }
    }

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found");
    }else{
        if(CurrToken.id == ";"){
            //consume the ';'
            declartion = new ASTVariableDeclNode(identifier,expr,type);
            CurrToken = lex.getNextToken();
        }else{
            Error("';' was not found");
        }
    }
    return declartion;
}

ASTStatementNode * Parser::ParseAssignment(){
    ASTAssignmentNode * statement = nullptr;
    ASTExpressionNode * identifier = nullptr;
    ASTExpressionNode * expr = nullptr;

    //consuming current token;
    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_identifier){
        Error("Identifier was not found in Variable Assignment");
    }else{
        //getting the new AST Identifier Node
        identifier = ParseIdentifier();
        //afterwards link the the ASTStatementNode
    }

    CurrToken = lex.getNextToken();
    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("'=' was not found in Variable Assignment");
    }else{
        if(CurrToken.id[0] != '='){
            Error("'=' was not found in Variable Assignment");
        }else{
            CurrToken = lex.getNextToken();
            //getting the new AST Expression Node
            expr = ParseExpression();
            //afterwards link the the ASTStatementNode
        }
    }

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found in Assignment");
    }else{
        if(CurrToken.id == ";"){
            //save the variable declaration to the program node
            //consume the ';'
            statement = new ASTAssignmentNode(identifier,expr);
            CurrToken = lex.getNextToken();
        }else{
            Error("';' was not found in Assignment");
        }

    }
    return statement;
}

ASTStatementNode * Parser::ParseWriteStatement(){

    ASTWriteNode * statement = nullptr;

    //consuming current token which is the write token;
    CurrToken = lex.getNextToken();
    ASTExpressionNode * expr = ParseExpression();

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("';' was not found in Write");
    }else{
        if(CurrToken.id[0] == ';'){
            //consume the ';'
            statement = new ASTWriteNode(expr);
            CurrToken = lex.getNextToken();
        }else{
            Error("';' was not found in Write");
        }
    }
    return statement;
}

ASTStatementNode * Parser::ParseReturnStatement() {
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

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("':' was not found in Function Declaration");
    }else{
        if(CurrToken.id != ":"){
            Error("':' was not found in Function Declaration");
        }else{
            CurrToken = lex.getNextToken();
        }
    }
    std::string type = CurrToken.id;

    //consuming the type
    CurrToken = lex.getNextToken();
    //link block to statment
    ASTStatementNode * block = ParseBlock();

    functionDecl = new ASTFunctionDeclNode(identifier,params,type,block);
    return functionDecl;
}

ASTStatementNode * Parser::ParseIfStatement(){
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

    if(CurrToken.token_type != Lexer::TOK_punc){
        Error("')' was not found in If Statement");
    }else{
        if(CurrToken.id != ")"){
            Error("')' was not found in If Statement");
        }else{
            CurrToken = lex.getNextToken();
        }
    }

    //link block to statement
    block = ParseBlock();
    if(CurrToken.token_type != Lexer::TOK_if){
        statement = new ASTIfStatementNode(expr,block,nullptr);
    }else{
        if(CurrToken.id != "else"){
            Error("'else' was not found in If Statement but if was found");
        }else{
            //consuming else
            CurrToken = lex.getNextToken();
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
    //Parse Block"
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

    //since a block is made up of statements, need to parse statement
    statement = ParseStatement();
    if(statement != nullptr) {
        block->addStatement(statement);
    }

    //if the next statement is not a } continue parsing statements until finding }
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

    //save it as a new expr
    //an expression must a simple expression as defined by the grammar
    ASTExpressionNode * simpleExpr = ParseSimpleExpression();

    //an expression can be made up of simple expression, or
    // simple expression relationOperation simple expression
    while(CurrToken.token_type == Lexer::TOK_realationOp){
        //saving them as a tree
        ASTExpressionNode * binOp = ParseBinaryOperation(2, simpleExpr);
        simpleExpr = binOp;
    }
    return simpleExpr;
}

ASTExpressionNode * Parser::ParseSimpleExpression(){
    //save it as a new SimpleExpr
    ASTExpressionNode * term = ParseTerm();

    //an simple expression can be made up of term, or
    // term addOperation term
    while(CurrToken.token_type == Lexer::TOK_addOp){
        //"Add Op found next"
        ASTExpressionNode * binOp = ParseBinaryOperation(1, term);
        term = binOp;
    }
    return term;
}

ASTExpressionNode * Parser::ParseTerm(){
    //save it as a new Term
    ASTExpressionNode * lhs = ParseFactor();

    //an term can be made up of a factor, or
    // factor multiplication Operation factor
    while(CurrToken.token_type == Lexer::TOK_multOp){
        //Mult Op found next
        ASTExpressionNode * binOp = ParseBinaryOperation(0, lhs);
        lhs = binOp;
    }
    return lhs;
}

ASTExpressionNode * Parser::ParseFactor(){
    /*
     * A factor is made up of the following
     *  Literal
     *      Boolean
     *      Integer
     *      Real
     *      String
     *  Identifier
     *  Function Call
     *  Sub Expression
     *  Unary
     */
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
                if(CurrToken.token_type != Lexer::TOK_punc){
                    Error("')' was not found in Function Call");
                }else{
                    if(CurrToken.id != ")"){
                        Error("')' was not found in Function Call");
                    }
                }
                ASTFunctionCallNode * funcCall = new ASTFunctionCallNode(ident,params);
                ans = funcCall;
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
            }   //return ans;
            else{
                Error("Token is of the incorrect format");
            }
            break;
        }

        case Lexer::TOK_unary: {
            ASTUnaryNode * unary = ParseUnary();
            return unary;
        }
        case Lexer::TOK_addOp:{
            if(CurrToken.id == "or"){
                Error("'or' found when '+'/ '-' was expected");
            }
            ASTExpressionNode * unary = ParseUnary();
            return unary;
        }
        default:{
            Error("Token was not recognised in Parse Factor");
        }
    }

    //consuming the factor
    CurrToken = lex.getNextToken();
    return ans;
}

ASTActualParametersNode * Parser::ParseActualParams(){
    //Parse Actual Params
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
}

ASTExpressionNode * Parser::ParseBinaryOperation(int prec, ASTExpressionNode * lhs){
    //Parse Binary Operation
    //link currToken (operation) to lhs then do the switch statement
    std::string operation = CurrToken.id;
    CurrToken = lex.getNextToken();
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
    //Entry in Parse Formal Param
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
    //Parse Formal Params
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
    std::string symbol = CurrToken.id;
    //consuming the unary token
    CurrToken = lex.getNextToken();

    ASTExpressionNode * expr = ParseExpression();

    ASTUnaryNode * unary = new ASTUnaryNode(symbol,expr);
    return unary;
}
