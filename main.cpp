#include "Lexer.h"
#include "Parser.h"
#include "Visitors/Visitor.h"
#include "Visitors/SemanticAnalysis.h"
#include "Visitors/InterpreterExecution.h"
//#include "InterpreterExecution.h"

int main() {
    std::cout << "Entry in Main" << std::endl;

    //Lexer *lex1 = new Lexer("/home/cps200x/Desktop/test.txt");
    Lexer *lex1 = new Lexer("/home/cps200x/ClionProjects/Assignment_5/test3");
    Parser * parser = new Parser(*lex1);
    auto rootNode = parser->Parse();


    XMLPrint * v = new XMLPrint();
    SemanticAnalysis * s = new SemanticAnalysis();
    InterpreterExecution *i = new InterpreterExecution();
    //rootNode->Accept(v);
    //rootNode->Accept(s);
    rootNode->Accept(i);


    //rootNode->XMLprint(0);
    return 0;
}
