//
// Created by cps200x on 5/18/16.
//

#include "REPL.h"

REPL::REPL() {
    this->eval = "";
    this->ans = 0;
    this->lex = new Lexer();
    this->parser = new Parser(*lex);

}

void REPL::evalution() {
    std::cout << "Instructions for this REPL Session" << std::endl;
    cmdFunctionPrint();
    while(this->eval != "#quit"){
        std::cout << "MLi> ";
        getline(std::cin,this->eval);
        if(this->eval[0] == '#'){
            if(this->eval == "#load"){

            }else if(this->eval == "#st"){

            }else if(this->eval == "#ans"){
                std::cout << this->ans << std::endl;
            }else if(this->eval == "#info"){
                cmdFunctionPrint();
            }else if(this->eval == "#quit"){
                break;
            }else{
                std::cout << "MLi> Incorrect Command Given" << std::endl;
                continue;
            }
        }

        std::cout << "Going into Lexer "<< std::endl;

        this->lex = new Lexer();
        this->parser = new Parser(*lex);

        this->lex->LexerRepl(this->eval);

        //auto rootNode = parser->Parse();




    }
    std::cout << "REPL Session ended" << std::endl;

}

void REPL::cmdFunctionPrint() {
    std::cout << "'#load' to load a script" << std::endl;
    std::cout << "'#quit' to end the session" << std::endl;
    std::cout << "'#st' display the contents of the symbol-table" << std::endl;
    std::cout << "'#ans' display most recent reuslt" << std::endl;
    std::cout << "'#info' print instructions" << std::endl;
}

