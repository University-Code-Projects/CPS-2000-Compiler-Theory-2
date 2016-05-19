//
// Created by cps200x on 5/6/16.
//

#ifndef ASSIGNMENT_5_LEXER_H
#define ASSIGNMENT_5_LEXER_H

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>

class Lexer {

public:

    Lexer();
    Lexer(std::string p_filename);
    Lexer(bool type,std::string p_filename);
    Lexer(bool text,Lexer&);
    virtual ~Lexer();

    //All possible token types and their associated value.
    /*
     * TOK_eof ---------- end of file reached
     * TOK_type --------- type of variable (int/real/bool/string)
     * TOK_bool --------- a token which is a boolean, contains true/ false
     * TOK_integer ------ a token which is an integer contains the value of the integer
     * TOK_realInt ------ a token which is a real contains the value of the real number
     * TOK_string ------- a token which is an string contains the value of the string
     * TOK_identifier --- a token which is an identifier contains the name of the identifier
     * TOK_multOp ------- a token which is an multiplication operation (* / and)
     * TOK_addOp -------- a token which is an additive operation (+ - or)
     * TOK_realationOp -- a token which is an additive operation ( < > != <= >= ==)
     * TOK_error -------- a token which is found is incorrect and cannot be stored as it is not defined in the EBNF
     * TOK_errorNum ----- a token which is an number but has the incorrect format example 2.369.58.1
     * TOK_punc --------- a token which is a punctuation that can store (= : ; ( ) { } ,)
     * TOK_def ---------- a token which is used to identify a function definition 'def'
     * TOK_set ---------- a token which is used to identify a variable assignment'set'
     * TOK_var ---------- a token which is used to identify a variable declaration 'var'
     * TOK_write -------- a token which is used to identify a write to output 'write'
     * TOK_if ----------- a token which is used to identify an if statement (if else)
     * TOK_while -------- a token which is used to identify a while loop 'while'
     * TOK_comment ------ a token which is used to identify when a single line comment or block comment is found
     * TOK_unary -------- a token used to identify a unary operation (for this case 'not'), even though the + and - are unary they are not saved as unary but checked in the parser
     * TOK_return ------- a token used to identify a return statement 'return'
     */
    enum TOK_Type{TOK_eof = -1, TOK_type = -2, TOK_bool = -3, TOK_integer = -4,
        TOK_realInt = -5, TOK_string = -6, TOK_identifier = -7,TOK_multOp = -8,
        TOK_addOp = -9, TOK_realationOp = -10, TOK_error = -11,TOK_errorNum = -12,
        TOK_punc = -13, TOK_def = -14, TOK_set = -15, TOK_var = -16,
        TOK_write = -17, TOK_if = -18 , TOK_while =-19, TOK_comment = -20,
        TOK_unary = -21 , TOK_return =-22};

    struct Token{
        TOK_Type token_type;
        std::string id;
        float num;

        Token(){
            token_type = TOK_eof;
            id = '"';
            num = 0;
        }

        Token(TOK_Type p_type, std::string p_id, float p_num ){
            token_type = p_type;
            id = p_id;
            num = p_num;
        }

        Token(TOK_Type p_type, char p_id, float p_num ){
            token_type = p_type;
            id = p_id;
            num = p_num;
        }

        Token(TOK_Type p_type, std::string p_id){
            token_type = p_type;
            id = p_id;
            num = 0;
        }

        Token(TOK_Type p_type, char p_id){
            token_type = p_type;
            id = p_id;
            num = 0;
        }

        Token(TOK_Type p_type, float p_num ){
            token_type = p_type;
            id = "";
            num = p_num;
        }

        std::string toString();
    };

    //use file to set contents of inputText
    std::string getProgramToText();

    // Get token impemented using Token type
    Token getNextToken();

    //check what the next token is
    Token tokenPeek();

private:
    bool text;

    std::ifstream file;//file given by user
    int charIndex;//current position in the inputText
    std::string inputText;//contents of the file

    std::string command;//intruction from repl

    float digitGet();//get digit
    std::string identifierGet();//get identifier
    std::string stringGet();//get string
    std::string commentGet();//get single comment
    std::string blockGet();//get block comment
    std::string relationalOpGet();//get relational operation
};




#endif //ASSIGNMENT_5_LEXER_H
