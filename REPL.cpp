//
// Created by cps200x on 5/18/16.
//

#include "REPL.h"
#include "Visitors/XMLPrint.h"
#include "Visitors/SemanticAnalysis.h"
#include "Visitors/InterpreterExecution.h"

///home/cps200x/ClionProjects/Assignment_5/test2


REPL::REPL() {

    file.clear();
    while(st.deleteScope()){
        st.deleteScope();
    }

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
            if(this->eval == "#st"){
                this->st.scopePrint();
            }else if(this->eval == "#ans"){
                std::cout << this->ans << std::endl;
            }else if(this->eval == "#info"){
                cmdFunctionPrint();
            }else if(this->eval == "#quit"){
                break;
            }else if((this->eval[1] == 'l')&&(this->eval[2] == 'o')&&(this->eval[3] == 'a')&&(this->eval[4] == 'd')){
                std::string fileName = "";

                //getting the file name
                //removing the #load, the whitespace and the first "
                for (int i =7; i < this->eval.size(); i++){
                    fileName+=this->eval[i];
                }
                if(this->loadFile(fileName)){
                    std::cout << "Script was opened" << std::endl;

                }else{
                    std::cout << "Script could not be opened" << std::endl;
                    break;
                }
            }else {
                std::cout << "Incorrect Command Given" << std::endl;
            }
            continue;
        }

        //std::cout << "Going into Lexer "<< std::endl;

        //Lexer *lex = new Lexer();
        this->lex->LexerRepl(this->eval);
        Parser * parser = new Parser(this->eval,*lex);
        auto rootNode = parser->ParseRepl();


        InterpreterExecution *i = new InterpreterExecution(this->st);
        rootNode->Accept(i);

        //this->lex = new Lexer();
        //this->parser = new Parser(*lex);



        //auto rootNode = parser->Parse();




    }
    std::cout << "REPL Session ended" << std::endl;

}

bool REPL::loadFile(std::string name) {

    std::cout << "Entry in load file" << std::endl;
    while(name[name.size()-1] != '"'){//removing any unwanted characters after the "
        name.pop_back();
    }
    //removing last "
    name.pop_back();

    file.open(name);
    if(file){
        std::cout << "File open was successful" << std::endl;

        Lexer *lex1 = new Lexer(name);
        Parser * parser = new Parser(*lex1);
        auto rootNode = parser->Parse();


        InterpreterExecution *i = new InterpreterExecution(this->st);
        rootNode->Accept(i);

        //Lexer(name);
        //Parser(*this->lex);
        //InterpreterExecution *i = new InterpreterExecution();

        //this->parser->Parse()->Accept(i);
        //i->st.scopePrint();

        std::cout << "PRINTING FROM REPL" << std::endl;
        this->st = i->st;
        this->st.scopePrint();

        return true;
    }else{
        return false;
    }






    return false;
}

void REPL::cmdFunctionPrint() {
    std::cout << "'#load' to load a script (must enter directory)" << std::endl;
    std::cout << "'#quit' to end the session" << std::endl;
    std::cout << "'#st' display the contents of the symbol-table" << std::endl;
    std::cout << "'#ans' display most recent reuslt" << std::endl;
    std::cout << "'#info' print instructions" << std::endl;
}

