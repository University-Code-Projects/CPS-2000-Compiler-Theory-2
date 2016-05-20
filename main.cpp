#include "Lexer.h"
#include "Parser.h"
#include "Visitors/XMLPrint.h"
#include "Visitors/SemanticAnalysis.h"
#include "Visitors/InterpreterExecution.h"
#include "REPL.h"

int main() {
    //std::cout << "Entry in Main" << std::endl;

    /*
    Lexer *lex1 = new Lexer("/home/cps200x/ClionProjects/Assignment_5/test3");
    Parser * parser = new Parser(false,*lex1);
    auto rootNode = parser->Parse();


    XMLPrint * v = new XMLPrint();
    SemanticAnalysis * s = new SemanticAnalysis();
    InterpreterExecution *i = new InterpreterExecution();



    rootNode->Accept(v);
    rootNode->Accept(s);
    rootNode->Accept(i);
    */
    REPL *r = new REPL();
    r->evalution();
    return 0;
}
