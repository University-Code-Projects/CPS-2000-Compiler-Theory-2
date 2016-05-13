#include "Lexer.h"
#include "Parser.h"
#include "Visitors/Visitor.h"
//#include "SemanticAnalysis.h"
//#include "InterpreterExecution.h"

int main() {
    std::cout << "Entry in Main" << std::endl;

    //Lexer *lex1 = new Lexer("/home/cps200x/Desktop/test.txt");
    Lexer *lex1 = new Lexer("/home/cps200x/ClionProjects/Assignment_5/test2");
    Parser * parser = new Parser(*lex1);
    auto rootNode = parser->Parse();

    std::cout << "After Parse" << std::endl;
    XMLPrint * v = new XMLPrint();
    //SemanticAnalysis * s = new SemanticAnalysis();
    //InterpreterExecution *i = new InterpreterExecution();
    rootNode->Accept(v);
    //rootNode->Accept(s);
    //rootNode->Accept(i);


    //rootNode->XMLprint(0);
    return 0;
}
