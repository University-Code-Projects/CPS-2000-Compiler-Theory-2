//
// Created by cps200x on 5/13/16.
//

#ifndef ASSIGNMENT_5_SYMBOLTABLE_H
#define ASSIGNMENT_5_SYMBOLTABLE_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>

class SymbolTable{
public:
    enum primitive_type{i=0, r=1, b =2,s=3,n=4};

    struct varValue{
        primitive_type t;
        int i;
        float r;
        bool b;
        std::string s;
    };
    struct funcValue{
        varValue t;
        std::vector<std::map< std::string,SymbolTable::varValue>> param;//using map since parameters cannot have same names
    };

    struct stValue{
        varValue vv;
        funcValue fv;
        bool func;

        stValue(primitive_type type){
            func = false;
            vv.t = type;
        }

        stValue(primitive_type type, bool function){
            func = true;
            fv.t.t = type;
        }

        stValue(primitive_type type, bool function,std::vector<std::map< std::string,SymbolTable::varValue>> funcParam){
            func = true;
            fv.t.t = type;
            fv.param = funcParam;
            //fv.param.push_back(funcParam);// = funcParam;
        }

    };

    //multimap used since map cannot have 2 strings of the same name (funcDec of same name, different types)
    std::vector<std::multimap<std::string, stValue>> scopeStack;

    //used by interpreter to get the value of the current type
    varValue varValues(primitive_type type){
        varValue variable;
        variable.t = type;
        variable.i =0;
        variable.r =0;
        variable.b =0;
        variable.s ="";
        return variable;
    }

    SymbolTable();

    //used by repl to insitiate the symbol table to the contents in the repl session
    SymbolTable(std::vector<std::multimap<std::string, stValue>> scopes);

    //create a new scope in the scopeStack
    bool createScope();

    //delete the most recent scope from the scopeStack
    bool deleteScope();

    //insert a variable
    bool insertInScope(std::string name, primitive_type type);

    //insert a function
    bool insertInScope(std::string name, primitive_type type, std::vector<std::map< std::string,SymbolTable::varValue>> funcParam);

    //check if an identifier is in the current scope or any other scope
    bool inScope(std::string name);

    //check if identifier is in the current scope only
    bool inCurrentScope(std::string name);

    //check if an identifier name is a parameter of the function fundName of type funcType
    bool isParam(std::string funcName,primitive_type funcType,std::string name);

    //used to print the scope
    void scopePrint();

    //get type of identifier/function call
    primitive_type getType(std::string name);

    //get type of the parameter name in the function funcName
    primitive_type getParamType(std::string funcName, std::string name);

    //setting the contents of a parameter when there is a function call
    bool setParamValue(std::string funcName,std::string name, int value);
    bool setParamValue(std::string funcName,std::string name, float value);
    bool setParamValue(std::string funcName,std::string name, bool value);
    bool setParamValue(std::string funcName,std::string name, std::string value);

    //getting the values of the return of a function
    int getIntValue(std::string funcName,std::string name);
    float getFloatValue(std::string funcName,std::string name);
    bool getBoolValue(std::string funcName,std::string name);
    std::string getStringValue(std::string funcName,std::string name);

    //setting a variable to the correct value given from the interpreter
    bool setValue(std::string name, int value);
    bool setValue(std::string name, float value);
    bool setValue(std::string name, bool value);
    bool setValue(std::string name, std::string value);

    //getting the value from the symbol table of a specific identifier
    int getIntValue(std::string name);
    float getFloatValue(std::string name);
    bool getBoolValue(std::string name);
    std::string getStringValue(std::string name);

    //setting the type of an identifier
    void setType(std::string name,primitive_type type);

};

#endif //ASSIGNMENT_5_SYMBOLTABLE_H
