#include "SymbolTable.h"

/*
 * Constructor used to delete all previous values of any scopes that were not closed
 */
SymbolTable::SymbolTable() {
    this->scopeStack.clear();
}

SymbolTable::SymbolTable(std::vector<std::multimap<std::string, stValue>> scopes) {
    SymbolTable();
    this->scopeStack = scopes;
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
bool SymbolTable::insertInScope(std::string name, SymbolTable::primitive_type type, std::vector<std::map< std::string,SymbolTable::varValue>> funcParam) {
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

bool SymbolTable::isParam(std::string funcName, primitive_type funcType, std::string name) {
    if(!this->inScope(funcName)) {//check if function exists in the scope
        return false;
    }else{
        std::multimap<std::string, stValue>::iterator mit;
        for(int i = 0; i < this->scopeStack.size(); i++) {
            for(mit = this->scopeStack.at(i).begin(); mit!=this->scopeStack.at(i).end(); mit++){
                if(mit->first == funcName){
                    std::map<std::string, varValue >::iterator it;
                    for(int i = 0; i < mit->second.fv.param.size(); i++){
                        for(it = mit->second.fv.param.at(i).begin();it != mit->second.fv.param.at(i).end(); it++ ){
                            if(it->first == name){//name given matches the parameter name
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
                        std::cout << " Value : " << mit->second.vv.i << "\t";
                        break;
                    case 1:
                        std::cout << " Type : " << "real   ";
                        std::cout << " Value : " << mit->second.vv.r << "\t";
                        break;
                    case 2:
                        std::cout << " Type : " << "bool   ";
                        std::cout << " Value : " ;
                        if(mit->second.vv.b){
                            std::cout << "true" << "\t";
                        } else{
                            std::cout << "false" << "\t";
                        }
                        break;
                    case 3:
                        std::cout << " Type : " << "string ";
                        std::cout << " Value : " << mit->second.vv.s << "\t";
                        break;

                }
            }else{
                switch (mit->second.fv.t.t) {
                    case 0:
                        std::cout << " Type : " << "int    ";
                        //std::cout << " Value : " << it->second.fv.t.i << "\t";
                        break;
                    case 1:
                        std::cout << " Type : " << "real   ";
                        //std::cout << " Value : " << it->second.fv.t.r << "\t";
                        break;
                    case 2:
                        std::cout << " Type : " << "bool   ";
                        //std::cout << " Value : " << it->second.fv.t.b << "\t";
                        break;
                    case 3:
                        std::cout << " Type : " << "string ";
                        //std::cout << " Value : " << it->second.fv.t.s << "\t";
                        break;

                }
                if(mit->second.fv.param.size() > 0){

                    //std::cout << "Parameters" << std::endl;
                    std::map<std::string, varValue>::iterator it;
                    //for(it = mit->second.fv.param.begin(); it != mit->second.fv.param.end())
                    for(int i = 0 ; i< mit->second.fv.param.size(); i++){
                        std::cout << " | Parameter Name : " << mit->second.fv.param.at(i).begin()->first <<"\t";
                        for(it = mit->second.fv.param.at(i).begin();it != mit->second.fv.param.at(i).end();it++) {
                            switch (it->second.t) {
                                case 0:
                                    std::cout << " Type : " << "int    ";
                                    //std::cout << " Value : " << it->second.i<< "\t";
                                    break;
                                case 1:
                                    std::cout << " Type : " << "real   ";
                                    //std::cout << " Value : " << it->second.r << "\t";
                                    break;
                                case 2:
                                    std::cout << " Type : " << "bool   ";
                                    //std::cout << " Value : " << it->second.b << "\t";
                                    break;
                                case 3:
                                    std::cout << " Type : " << "string ";
                                    //std::cout << " Value : " << it->second.s << "\t";
                                    break;

                            }
                            //std::cout << " Parameter Type : " << mit->second.fv.param.at(i).begin()->second.t<<"\t";
                        }
                    }

                }
            }

            std::cout << "\n";
        }
    }
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
    //std::cerr << "Type : " << typePrint(this->Type) << std::endl;

    if(inScope((funcName))){
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
            for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                return it->second.t;
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

bool SymbolTable::setParamValue(std::string funcName,std::string name, int value) {
    //std::cerr << "Type : " << typePrint(this->Type) << std::endl;
    if(inScope((funcName))){
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                it->second.i = value;
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }else{
        return false;
    }
}

bool SymbolTable::setParamValue(std::string funcName,std::string name, float value) {
    if(inScope((funcName))){
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                it->second.r = value;
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }else{
        return false;
    }
}

bool SymbolTable::setParamValue(std::string funcName,std::string name, bool value) {
    //std::cerr << "Type : " << typePrint(this->Type) << std::endl;
    if(inScope((funcName))){
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                it->second.b = value;
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }else{
        return false;
    }
}

bool SymbolTable::setParamValue(std::string funcName,std::string name, std::string value) {
    if(inScope((funcName))){
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue >::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++ ){
                            if(it->first == name){
                                it->second.s = value;
                                return true;
                            }
                        }

                    }
                }
            }
        }
    }else{
        return false;
    }
}

int SymbolTable::getIntValue(std::string funcName,std::string name) {
    if (inScope(funcName)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue>::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++){
                            if(it->first == name){
                                return it->second.i;
                            }
                        }
                    }
                }
            }
        }
    }
}

float SymbolTable::getFloatValue(std::string funcName,std::string name) {
    if (inScope(funcName)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue>::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++){
                            if(it->first == name){
                                return it->second.r;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool SymbolTable::getBoolValue(std::string funcName,std::string name) {
    if (inScope(funcName)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue>::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++){
                            if(it->first == name){
                                return it->second.b;
                            }
                        }
                    }
                }
            }
        }
    }
}

std::string SymbolTable::getStringValue(std::string funcName,std::string name) {
    if (inScope(funcName)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == funcName){
                    std::map<std::string, varValue>::iterator it;
                    for(int j =0; j < mit->second.fv.param.size(); j++){
                        for(it = mit->second.fv.param.at(j).begin();it != mit->second.fv.param.at(j).end(); it++){
                            if(it->first == name){
                                return it->second.s;
                            }
                        }
                    }
                }
            }
        }
    }
}

bool SymbolTable::setValue(std::string name, int value) {
    if (inScope(name)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){
                    if(mit->second.func == true){
                        mit->second.fv.t.i = value;
                        //std::cerr << "Cannot modify Value of a function" << std::endl;
                    }else{
                        //this->scopeStack.at(this->scopeStack.size()-i-1).
                        mit->second.vv.i = value;
                        return true;
                    }
                }
            }
        }
    } else {
        return false;
    }
}

bool SymbolTable::setValue(std::string name, float value) {
    if (inScope(name)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){
                    if(mit->second.func == true){
                        mit->second.fv.t.r = value;
                        return true;
                        //std::cerr << "Cannot modify Value of a function" << std::endl;
                    }else{
                        //this->scopeStack.at(this->scopeStack.size()-i-1).
                        mit->second.vv.r = value;
                        return true;
                    }
                }
            }
        }
    } else {
        return false;
    }
}

bool SymbolTable::setValue(std::string name, bool value) {
    if (inScope(name)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){
                    if(mit->second.func == true){
                        mit->second.fv.t.b = value;
                        //std::cerr << "Cannot modify Value of a function" << std::endl;
                    }else{
                        //this->scopeStack.at(this->scopeStack.size()-i-1).
                        mit->second.vv.b = value;
                        return true;
                    }
                }
            }
        }
    } else {
        return false;
    }
}

bool SymbolTable::setValue(std::string name, std::string value) {
    if (inScope(name)) {
        for(int i = 0 ; i < this->scopeStack.size(); i ++){
            std::multimap<std::string, stValue>::iterator mit;
            for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
                if(mit->first == name){
                    if(mit->second.func == true){
                        mit->second.fv.t.s = value;
                        //std::cerr << "Cannot modify Value of a function" << std::endl;
                    }else{
                        //this->scopeStack.at(this->scopeStack.size()-i-1).
                        mit->second.vv.s = value;
                        return true;
                    }
                }
            }
        }
    } else {
        return false;
    }
}

int SymbolTable::getIntValue(std::string name) {
    for(int i = 0 ; i < this->scopeStack.size(); i ++){
        std::multimap<std::string, stValue>::iterator mit;
        std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
        for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name){
                if(mit->second.func){
                    return mit->second.fv.t.i;
                }else {
                    return mit->second.vv.i;
                }
            }
        }
    }
}

float SymbolTable::getFloatValue(std::string name) {
    for(int i = 0 ; i < this->scopeStack.size(); i ++){
        std::multimap<std::string, stValue>::iterator mit;
        std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
        for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name) {
                if (mit->second.func) {
                    return mit->second.fv.t.r;
                } else {
                    return mit->second.vv.r;
                }
            }
        }
    }
}

bool SymbolTable::getBoolValue(std::string name) {
    for(int i = 0 ; i < this->scopeStack.size(); i ++){
        std::multimap<std::string, stValue>::iterator mit;
        std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
        for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name){
                if(mit->second.func){
                    return mit->second.fv.t.b;
                }else {
                    return mit->second.vv.b;
                }
            }
        }
    }
}

std::string SymbolTable::getStringValue(std::string name) {
    for(int i = 0 ; i < this->scopeStack.size(); i ++){
        std::multimap<std::string, stValue>::iterator mit;
        std::multimap<std::string, stValue> curr = this->scopeStack.at(this->scopeStack.size()-i-1);
        for(mit = curr.begin(); mit != curr.end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name){
                if(mit->second.func){
                    return mit->second.fv.t.s;
                }else {
                    return mit->second.vv.s;
                }
            }

        }
    }
}

void SymbolTable::setType(std::string name,primitive_type type) {
    for(int i = 0 ; i < this->scopeStack.size(); i ++){
        std::multimap<std::string, stValue>::iterator mit;
        for(mit = this->scopeStack.at(this->scopeStack.size()-i-1).begin(); mit != this->scopeStack.at(this->scopeStack.size()-i-1).end(); mit++) {//should only iterate once as one 1 map per vector
            if(mit->first == name){
                //this->scopeStack.at(this->scopeStack.size()-i-1).
                mit->second.vv.t = type;
                return;
            }
        }
    }
}
