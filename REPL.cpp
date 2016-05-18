//
// Created by cps200x on 5/18/16.
//

#include "REPL.h"
#include "Visitors/XMLPrint.h"
#include "Visitors/SemanticAnalysis.h"
#include "Visitors/InterpreterExecution.h"

//#load "/home/cps200x/ClionProjects/Assignment_5/test2"

REPL::REPL() {
    file.clear();
    while(st.deleteScope()){
        st.deleteScope();
    }

    this->eval = "";

    in =0;
    fl= 0.0;
    bo = false;
    str = "";

    this->lex = new Lexer();
    this->parser = new Parser(false,*lex);
    i = new InterpreterExecution(this->st);
    this->funcCall = nullptr;
}

void REPL::evalution() {
    cmdFunctionPrint();
    while(this->eval != "#quit"){
        std::cout << "MLi> ";
        getline(std::cin,this->eval);
        if(this->eval[0] == '#'){
            if(this->eval == "#st"){
                this->st.scopePrint();
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

                }else{
                    std::cout << "Script could not be opened" << std::endl;
                    //break;
                }
            }else {
                std::cout << "Incorrect Command Given" << std::endl;
            }
            continue;
        }


        switch (i->typeGet()){

        }

        Lexer *lex = new Lexer(false, this->eval);
        Parser * parser = new Parser(true,*lex);

        auto rootNode = parser->ParseRepl();

        *i = InterpreterExecution(this->st);
        //std::cout << "After Parse" << std::endl;
        i->funcCallSet(funcCall);
        XMLPrint * v = new XMLPrint();
        rootNode->Accept(v);

        rootNode->Accept(i);
        if(!(i->sem)){
            this->st = i->st;
            ansResult(i->typeGet());
        }
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
        Parser * parser = new Parser(false,*lex1);
        auto rootNode = parser->Parse();


        *i = InterpreterExecution(this->st);
        rootNode->Accept(i);
        funcCall = i->funcCallGet();
        //Lexer(name);
        //Parser(*this->lex);
        //InterpreterExecution *i = new InterpreterExecution();

        //this->parser->Parse()->Accept(i);
        //i->st.scopePrint();

        //std::cout << "PRINTING FROM REPL" << std::endl;

        this->st = i->st;
        //this->st.scopePrint();
        std::cout << "Script was opened" << std::endl;
        //file.close();
        return true;
    }else{
        return false;
    }
}

void REPL::cmdFunctionPrint() {
    std::cout << "---------------Instructions for this REPL Session---------------" << std::endl;
    std::cout << "'#load' to load a script (must enter directory)" << std::endl;
    std::cout << "'#quit' to end the session" << std::endl;
    std::cout << "'#st' display the contents of the symbol-table" << std::endl;
    std::cout << "'#info' print instructions" << std::endl;
}

void REPL::ansResult(SymbolTable::primitive_type type){
    switch (type){
        case 0:
            in = std::stoi(i->valuePrint(type));
            std::cout << "Val ans : int = " << in << std::endl;
            fl =0;
            bo = false;
            str = "";
            break;
        case 1:
            fl = std::stof(i->valuePrint(type));
            std::cout << "Val ans : real = "<< fl << std::endl;
            in =0;
            bo = false;
            str = "";
            break;
        case 2:
            //bo = std::sto st(i->valuePrint(type));
            if(i->valuePrint(type) == "true"){
                bo = true;
            }else{
                bo = false;
            }
            std::cout << "Val ans : bool = " <<  i->valuePrint(type)<< std::endl;
            fl =0;
            in = 0;
            str = "";
            break;
        case 3:
            std::cout << "Val ans : string = " << i->valuePrint(type)<< std::endl;
            str = i->valuePrint(type);
            fl =0;
            bo = false;
            in = 0;
            break;
    }
    if(this->st.inScope("ans")){
        if(this->st.getType("ans") == i->typeGet()){
            switch (i->typeGet()){
                case 0:
                    this->st.setValue("ans",in);
                    break;
                case 1:
                    this->st.setValue("ans",fl);
                    break;
                case 2:
                    this->st.setValue("ans",bo);
                    break;
                case 3:
                    this->st.setValue("ans",str);
                    break;
            }
        }else{
            this->st.setType("ans",i->typeGet());
                switch (i->typeGet()){
                    case 0:
                        this->st.setValue("ans",in);
                        break;
                    case 1:
                        this->st.setValue("ans",fl);
                        break;
                    case 2:
                        this->st.setValue("ans",bo);
                        break;
                    case 3:
                        this->st.setValue("ans",str);
                        break;
                }
        }
    }else{
        this->st.insertInScope("ans",i->typeGet());
        switch (i->typeGet()){
            case 0:
                this->st.setValue("ans",in);
                break;
            case 1:
                this->st.setValue("ans",fl);
                break;
            case 2:
                this->st.setValue("ans",bo);
                break;
            case 3:
                this->st.setValue("ans",str);
                break;
        }
    }
}
