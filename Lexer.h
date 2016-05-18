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

    Lexer(std::string p_filename);
    Lexer(Lexer&);
    virtual ~Lexer();

    Lexer();
    void LexerRepl(std::string command);
    void LexerRepl(Lexer&);


    //All possible token types and their associated value.
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

    std::string getProgramToText();

    // Get token impemented using Token type
    Token getNextToken();

    Token tokenPeek();

private:
    std::ifstream file;
    int charIndex;
    std::string inputText;

    std::string command;

    float digitGet();
    std::string identifierGet();
    std::string stringGet();
    std::string commentGet();
    std::string blockGet();
    std::string relationalOpGet();
};




#endif //ASSIGNMENT_5_LEXER_H
