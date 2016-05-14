cmake_minimum_required(VERSION 3.3)
project(Assignment_5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h ASTNodes/ASTNode.h Visitors/Visitor.h ASTNodes/Include.h ASTNodes/ASTExpressionNode.h ASTNodes/ASTStatementNode.h ASTNodes/ASTIfStatementNode.h ASTNodes/ASTProgramNode.h ASTNodes/ASTBlockNode.h ASTNodes/ASTWhileNode.h ASTNodes/ASTReturnNode.h ASTNodes/ASTWriteNode.h ASTNodes/ASTFunctionDeclNode.h ASTNodes/ASTFormalParametersNode.h ASTNodes/ASTFormalParameterNode.h ASTNodes/ASTVariableDeclNode.h ASTNodes/ASTAssignmentNode.h ASTNodes/ASTIdentifierNode.h ASTNodes/ASTBoolNode.h ASTNodes/ASTFloatNode.h ASTNodes/ASTIntegerNode.h ASTNodes/ASTStringNode.h ASTNodes/ASTUnaryNode.h ASTNodes/ASTBinaryNode.h ASTNodes/ASTSubExpressionNode.h ASTNodes/ASTFunctionCallNode.h ASTNodes/ASTActualParametersNode.h Visitors/XMLPrint.cpp Visitors/XMLPrint.h SymbolTable.cpp SymbolTable.h Visitors/SemanticAnalysis.cpp Visitors/SemanticAnalysis.h)
add_executable(Assignment_5 ${SOURCE_FILES})