#include "SymbolTable.h"

/*
 * Constructor used to delete all previous values of any scopes that were not closed
 */
SymbolTable::SymbolTable() {
    this->scopeStack.clear();
}

/*
 * Creating a Scope on top (most recent)
 */
bool SymbolTable::createScope() {
    std::multimap<std::string, stValue> newScope;
    this->scopeStack.push_back(newScope);
    return true;
}

/*
 * Deleting the most recent Scope
 */
bool SymbolTable::deleteScope() {

    if(this->scopeStack.size() < 1){
        //this->scopePrint();
        return false;
    }else {
        this->scopeStack.pop_back();
        return true;
    }
}

/*
 * Adding a Variable to the Scope
 */
bool SymbolTable::insertInScope(std::string name, SymbolTable::primitive_type type) {
    std::pair<std::string, stValue> pair(name, stValue(type));
    this->scopeStack.at(this->scopeStack.size()-1).insert(pair);
    return true;
}

/*
 * Adding a Function to the scope
 */
bool SymbolTable::insertInScope(std::string name, SymbolTable::primitive_type type, std::vector<std::map< std::string,SymbolTable::primitive_type>> funcParam) {
    std::pair<std::string, stValue> pair(name, stValue(type,true,funcParam));
    this->scopeStack.at(this->scopeStack.size()-1).insert(pair);
    return true;
}

/*
 * Check if the Variable is defined anywhere in the scope
 */
bool SymbolTable::inScope(std::string name) {
    std::multimap<std::string, stValue>::iterator mit;
    for(int i = 0; i < this->scopeStack.size(); i++) {
        std::multimap<std::string, stValue> curr =this->scopeStack.at(i);
        for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name){
                return true;
            }
        }
    }
    return false;
}

/*
 * Check if an Identifier is in the Current top Scope
 */
bool SymbolTable::inCurrentScope(std::string name) {

    std::multimap<std::string, stValue>::iterator mit;
    std::multimap<std::string, stValue> curr =this->scopeStack.at(this->scopeStack.size()-1);
    for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
        if(mit->first == name){
            return true;
        }
    }
    return false;
}

/*
 * Used to check if a variable is a parameter of a function or not
 */
/*
bool SymbolTable::isParam(std::string funcName,primitive_type funcType,std::string name) {
    if(!this->inScope(funcName)){//check if function exists in the scope
        return false;
    }else{
        std::multimap<std::string, stValue>::iterator mit;
        for(int i = 0; i < this->scopeStack.size(); i++) {
            std::multimap<std::string, stValue> curr =this->scopeStack.at(i);

            for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){//check function name
                    if(mit->second.fv.t.t == funcType){//and function type
                        std::multimap<std::string, primitive_type>::iterator pit;

                        for(int j = 0; j < mit->second.fv.param.size(); j++){//iterating the parameters of vectors
                            std::map<std::string, primitive_type> param = mit->second.fv.param.at(i);

                            for(pit = param.begin(); pit != param.end(); pit++){//iterating the map (should only iterate once
                                if(pit->first == name){//checking if parameter is found
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

}
*/

bool SymbolTable::isParam(std::string funcName, primitive_type funcType, std::string name) {
    if(!this->inScope(funcName)) {//check if function exists in the scope
        return false;
    }else{
        std::multimap<std::string, stValue>::iterator mit;
        for(int i = 0; i < this->scopeStack.size(); i++) {
            for(mit = this->scopeStack.at(i).begin(); mit!=this->scopeStack.at(i).end(); mit++){
                if(mit->first == funcName){
                    std::map<std::string, primitive_type >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                return true;
                            }
                        }

                    }

                }
            }
        }
    }
    return false;
}

/*
 * Printing the Scope for testing
 */
void SymbolTable::scopePrint() {
    std::cout << "Printing Scope" << std::endl;
    std::multimap<std::string, stValue>::iterator mit;

    for(int i = 0; i < this->scopeStack.size(); i++){
        std::multimap<std::string, stValue> curr =this->scopeStack.at(i);
        std::cout << "Level : " << i << std::endl;
        for(mit = curr.begin(); mit != curr.end(); mit++){//should only iterate once as one 1 map per vector
            std::cout << "Name : " << mit->first <<"\t" ;

            if(mit->second.func == false) {

                switch (mit->second.vv.t) {
                    case 0:
                        std::cout << " Type : " << "int    ";
                        //std::cout << " Value : " << it->second.vv.Data.i << "\t";
                        break;
                    case 1:
                        std::cout << " Type : " << "real   ";
                        //std::cout << " Value : " << it->second.vv.Data.r << "\t";
                        break;
                    case 2:
                        std::cout << " Type : " << "bool   ";
                        //std::cout << " Value : " << it->second.vv.Data.b << "\t";
                        break;
                    case 3:
                        std::cout << " Type : " << "string ";
                        //std::cout << " Value : " << it->second.vv.s << "\t";
                        break;

                }
            }else{
                switch (mit->second.fv.t.t) {
                    case 0:
                        std::cout << " Type : " << "int    ";
                        //std::cout << " Value : " << it->second.fv.t.Data.i << "\t";
                        break;
                    case 1:
                        std::cout << " Type : " << "real   ";
                        //std::cout << " Value : " << it->second.fv.t.Data.r << "\t";
                        break;
                    case 2:
                        std::cout << " Type : " << "bool   ";
                        //std::cout << " Value : " << it->second.fv.t.Data.b << "\t";
                        break;
                    case 3:
                        std::cout << " Type : " << "string ";
                        //std::cout << " Value : " << it->second.fv.t.s << "\t";
                        break;

                }
                if(mit->second.fv.param.size() > 0){

                    //std::cout << "Parameters" << std::endl;
                    for(int i = 0 ; i< mit->second.fv.param.size(); i++){
                        std::cout << " | Parameter Name : " << mit->second.fv.param.at(i).begin()->first <<"\t";

                        std::cout << " Parameter Type : " << mit->second.fv.param.at(i).begin()->second<<"\t";

                    }

                }
            }

            std::cout << "\n";
        }
    }
    /*
    for(it = this->scopeStack.begin(); it != this->scopeStack.end(); it++){


    }
    */
}

SymbolTable::primitive_type SymbolTable::getType(std::string name) {
    if(inCurrentScope(name)){
        std::multimap<std::string, stValue>::iterator mit;
        std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-1);
        for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name){
                if(mit->second.func == true){
                    return mit->second.fv.t.t;
                }else{
                    return mit->second.vv.t;
                }
            }
        }
    }else{
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
            for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){
                    if(mit->second.func == true){
                        return mit->second.fv.t.t;
                    }else{
                        return mit->second.vv.t;
                    }
                }
            }
        }
    }
}

SymbolTable::primitive_type SymbolTable::getParamType(std::string funcName,std::string name) {
    if(inScope((funcName))){
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
            for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){
                    std::map<std::string, primitive_type >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                return it->second;
                            }
                        }

                    }
                }
            }
        }
    }else{
        return n;
    }
}
/*
SymbolTable::primitive_type SymbolTable::getParamType(std::string funcName,std::string name) {
    std::map<std::string, stValue>::iterator mit;
    std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-1);

    for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
        if(mit->first == funcName){

            std::map<std::string, SymbolTable::primitive_type >::iterator it;
            for(int i = 0; i < mit->second.fv.param.size(); i++){

                for(it = mit->second.fv.param.at(i).begin(); it !=mit->second.fv.param.at(i).end(); it++){
                    if(it->first == name){
                        return it->second;
                    }
                }
            }
        }
    }
}
*/