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

    bool createScope();
    bool deleteScope();

    bool insertInScope(std::string name, primitive_type type);
    bool insertInScope(std::string name, primitive_type type, std::vector<std::map< std::string,SymbolTable::varValue>> funcParam);

    bool inScope(std::string name);

    bool inCurrentScope(std::string name);

    bool isParam(std::string funcName,primitive_type funcType,std::string name);

    void scopePrint();

    primitive_type getType(std::string name);
    primitive_type getParamType(std::string funcName, std::string name);

    bool setParamValue(std::string funcName,std::string name, int value);
    bool setParamValue(std::string funcName,std::string name, float value);
    bool setParamValue(std::string funcName,std::string name, bool value);
    bool setParamValue(std::string funcName,std::string name, std::string value);

    int getIntValue(std::string funcName,std::string name);
    float getFloatValue(std::string funcName,std::string name);
    bool getBoolValue(std::string funcName,std::string name);
    std::string getStringValue(std::string funcName,std::string name);





    bool setValue(std::string name, int value);
    bool setValue(std::string name, float value);
    bool setValue(std::string name, bool value);
    bool setValue(std::string name, std::string value);

    int getIntValue(std::string name);
    float getFloatValue(std::string name);
    bool getBoolValue(std::string name);
    std::string getStringValue(std::string name);
};

#endif //ASSIGNMENT_5_SYMBOLTABLE_H
