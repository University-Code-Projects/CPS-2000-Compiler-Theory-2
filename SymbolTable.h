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
        union Data{
            int i;
            float r;
            bool b;
        }Data;
        std::string s;
    };
    struct funcValue{
        varValue t;
        std::vector<std::map< std::string,SymbolTable::primitive_type>> param;//using map since parameters cannot have same names
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

        stValue(primitive_type type, bool function,std::vector<std::map< std::string,SymbolTable::primitive_type>> funcParam){
            func = true;
            fv.t.t = type;
            fv.param = funcParam;
            //fv.param.push_back(funcParam);// = funcParam;
        }

    };

    //multimap used since map cannot have 2 strings of the same name (funcDec of same name, different types)
    std::vector<std::multimap<std::string, stValue>> scopeStack;

    SymbolTable();

    bool createScope();
    bool deleteScope();

    bool insertInScope(std::string name, primitive_type type);
    bool insertInScope(std::string name, primitive_type type, std::vector<std::map< std::string,SymbolTable::primitive_type>> funcParam);

    bool inScope(std::string name);

    bool inCurrentScope(std::string name);

    bool isParam(std::string funcName,primitive_type funcType,std::string name);

    //bool setParam(std::string funcName, std::string name,primitive_type type);

    //int getNoOfParam(std::string name, primitive_type type);
    //std::vector<std::map< std::string,SymbolTable::primitive_type>> getFuncParam(std::string name, primitive_type type);

    void scopePrint();

    primitive_type getType(std::string name);
    primitive_type getParamType(std::string funcName, std::string name);

    //std::vector<std::map< std::string,SymbolTable::primitive_type>> getParam(std::string name, primitive_type type);
};

#endif //ASSIGNMENT_5_SYMBOLTABLE_H
