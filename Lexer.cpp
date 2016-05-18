//
// Created by cps200x on 5/6/16.
//

#include "Lexer.h"

/*
 * Constructor, exit if file is not unacceptable
 */
Lexer::Lexer(std::string p_filename) {
    file.open(p_filename);
    if(file){
        std::cout << "File '" << p_filename << "' was opened successfully." << std::endl;
        text = false;
    }else{
        std::cout << "File '" << p_filename << "' could no be opened." << std::endl;
    }
}
Lexer::Lexer(bool type,std::string p_filename) {
    //std::cout << "Entry in this constrctor : " << std::endl;
    if (type) {
        std::cout << " file " << std::endl;
        file.open(p_filename);
        if (file) {
            std::cout << "File '" << p_filename << "' was opened successfully." << std::endl;
            text = false;
        } else {
            std::cout << "File '" << p_filename << "' could no be opened." << std::endl;
        }
    }else{
        //std::cout << " text " << std::endl;
        command = p_filename + "  ";
        text = true;
    }

}
Lexer::Lexer(bool text,Lexer &Lex) {
    //std::cout << "Address: " << &Lex << std::endl;
    if (text) {
        inputText = Lex.command;
    } else {
        inputText = Lex.getProgramToText();
    }
    charIndex = 0;
    //std::cout << "From the constructor itself"<<std::endl<< inputText << std::endl;
}

Lexer::~Lexer() {
    std::cout << "Object was deconstructed" << std::endl;
}


Lexer::Lexer() {}

/*
void Lexer::LexerRepl(std::string com) {
    std::cout << "Entry in Lex Repl : " << com << std::endl;
    command = com;
    std::cout << command << std::endl;
    inputText = command;
    std::cout << "Input text " << inputText<< std::endl;
}
*/
//void Lexer::LexerRepl(Lexer &lexer) {
//    std::cout << "Entry in Lex Repl &" << std::endl;
//    inputText = lexer.inputText;
//    charIndex =0;
//}

std::string Lexer::getProgramToText(){
    std::cout << "Entry in program to text function" << std::endl;
    std::string currentLine = "";
    inputText = "";//initializing the private var that stores the entire project as a string/char
    charIndex = 0;
    bool eoffound = false;



    while(getline(file, currentLine)){

        if(file.eof()) {
            eoffound = true;
            break;
        }

        if(eoffound == false){
            int size = currentLine.length();
            int curr=0;
            curr++;
            if(curr <= size){
                inputText += currentLine;
            }
            if((currentLine.length()-1) ==  '\r'|| '\t') {
                inputText += ' ';
            }
            if(file.peek() != EOF){
                inputText += '\n';

            }else{
                break;
            }
        }

    }
    std::cout << "Length of Text: " << inputText.length()<<std::endl;
    return inputText;
}

std::string Lexer::blockGet(){
    char lastChar = inputText[charIndex];
    std::string ret = "";
    ret+= lastChar;
    charIndex++;
    lastChar = inputText[charIndex];
    while(true){

        if(lastChar == '*'){
            ret += lastChar;
            charIndex++;
            lastChar = inputText[charIndex];
            if(lastChar == '/'){
                ret += lastChar;
                charIndex++;
                break;
            }
        }
        ret+= lastChar;
        charIndex++;
        lastChar = inputText[charIndex];

    }
    return ret;
}

std::string Lexer::stringGet(){
    char lastChar = inputText[charIndex];
    std::string ret = "";
    ret+= lastChar;
    charIndex++;
    lastChar = inputText[charIndex];
    while(isprint((int)lastChar)){
        if(((int)lastChar < 32) || ((int)lastChar > 126)){
            charIndex++;
            break;
        }
        if(lastChar == '"'){
            ret += lastChar;
            charIndex++;
            break;
        }
        ret+= lastChar;
        charIndex++;
        lastChar = inputText[charIndex];

    }
    return ret;
}

std::string Lexer::identifierGet(){
    char lastChar = inputText[charIndex];
    std::string word = "";
    while((isalpha(lastChar))||(isdigit(lastChar))||(lastChar == '_')){
        word+=lastChar;
        charIndex++;
        lastChar = inputText[charIndex];
    }
    return word;
}

float Lexer::digitGet() {
    char lastChar = inputText[charIndex];
    std::string curr = "";
    std::string::size_type sz;
    float num =0;

    if(lastChar == '.'){
        curr += lastChar;//since 1st char is a .
        charIndex++;
        lastChar = inputText[charIndex];
    }
    while(isdigit(lastChar)){
        curr += lastChar;
        charIndex++;
        lastChar = inputText[charIndex];
    }
    num = stof(curr, &sz);
    return num;
}

std::string Lexer::relationalOpGet(){
    char lastChar = inputText[charIndex];
    std::string boolOp = "";
    boolOp += lastChar;
    charIndex++;
    if(inputText[charIndex] == '='){
        boolOp+= inputText[charIndex];
        charIndex++;
    }
    return boolOp;
}

std::string Lexer::commentGet() {
    char lastChar = inputText[charIndex];
    std::string comment;

    comment+= lastChar;
    charIndex++;
    lastChar = inputText[charIndex];
    while(lastChar != '\n'){
        comment += lastChar;
        charIndex++;
        lastChar = inputText[charIndex];

    }
    return comment;
}

Lexer::Token Lexer::getNextToken() {
    if((unsigned int) charIndex == inputText.length()){
        //std::cout << "char index == length" << std::endl;
        return (Lexer::Token());
    }
    char lastChar = inputText[charIndex];
    while(charIndex != inputText.length()-1) {
        while ((isspace(lastChar) || lastChar == '\n') && lastChar != EOF) {//skipping any whitespaces
            charIndex++;
            lastChar = inputText[charIndex];
        }
        if (lastChar == EOF) {
            return (Lexer::Token());
        }

        if (isdigit(lastChar) || (lastChar == '.')) {//get integer / real number
            float num = 0;
            float ans = 0;
            if (isdigit(lastChar)) {
                num = digitGet();
                ans = int(num);
            }
            lastChar = inputText[charIndex];
            if (lastChar == '.') {
                ans = num + digitGet();
                lastChar = inputText[charIndex];
                if (lastChar == '.') {
                    std::string inco = "";
                    while ((lastChar == '.') || (isdigit(lastChar))) {
                        inco += lastChar;
                        charIndex++;
                        lastChar = inputText[charIndex];
                    }
                    std::string error = "Float Error, has more than 1 decimal point at :";
                    error += std::to_string(ans);
                    error += inco;
                    return (Lexer::Token(TOK_errorNum, error));
                } else {
                    if(isalpha(lastChar)){
                        return (Lexer::Token(TOK_error, "Next Character is not a space, undefined reference"));
                    }else{
                        return (Lexer::Token(TOK_realInt,ans));
                    }
                }
            } else {
                if(isalpha(lastChar)){
                    std::string error = "Next Character is not a space, undefined reference from : ";
                    error += std::to_string((int)ans);
                    error += identifierGet();
                    return (Lexer::Token(TOK_error, error));
                }else{
                    return (Lexer::Token(TOK_integer,ans));
                }
            }
        }

        if (lastChar == '"') {//get string
            std::string stringLit = stringGet();
            return (Lexer::Token(TOK_string, stringLit));
        }

        if(lastChar == '/') {//for comments
            charIndex++;
            if (inputText[charIndex] == '/') {
                std::string comm = "";
                comm += lastChar;
                comm += commentGet();
                //getNextToken();
                return Lexer::Token(TOK_comment, comm);
            }else if (inputText[charIndex] == '*'){
                std::string comm = "";
                comm += lastChar;
                comm += blockGet();
                //std::cout << "Comment" << comm << std::endl;
                return Lexer::Token(TOK_comment, comm);
            }else{
                return  (Lexer::Token(TOK_multOp,lastChar));
            }
        }

        if((lastChar == '+') || (lastChar == '-') ||(lastChar == '*') ||(lastChar == '/')){
            charIndex++;
            if((lastChar == '+') || (lastChar == '-')){
                return (Lexer::Token(TOK_addOp,lastChar));
            }else{
                return  (Lexer::Token(TOK_multOp,lastChar));
            }
        }

        if((lastChar == '>')||(lastChar == '<')||(lastChar == '=')||(lastChar == '!')){
            std::string boolop = relationalOpGet();
            if(boolop.length() == 2){
                //char equal = boolop[0];
                //if(equal == '='){
                //    return (Lexer::Token(TOK_punc, equal));
                //}else{
                return (Lexer::Token(TOK_realationOp,boolop));
                //}
            }else{
                char equal = boolop[0];
                if(equal == '='){
                    return (Lexer::Token(TOK_punc, equal));
                }else{
                    return (Lexer::Token(TOK_realationOp,boolop[0]));
                }

                //return (Lexer::Token(TOK_realationOp,boolop));
            }
        }

        if((lastChar == '=')||(lastChar == ':')||(lastChar == ';')||(lastChar == '(')||(lastChar == ')')||(lastChar == '{')||(lastChar == '}')||(lastChar == ',')){
            charIndex++;
            return (Lexer::Token(TOK_punc,lastChar));
        }

        if ((lastChar == '_') || (isalpha(lastChar))) {
            std::string word = identifierGet();
            if ((word == "real") || (word == "int") || (word == "bool") || (word == "string")) {
                return (Lexer::Token(TOK_type, word));
            } else if ((word == "true") || (word == "false")) {
                return (Lexer::Token(TOK_bool, word));
            } else if ((word == "and") || (word == "or") || (word == "not")) {
                if (word == "and") {
                    return (Lexer::Token(TOK_multOp, word));
                } else if (word == "or") {
                    return (Lexer::Token(TOK_addOp, word));
                } else {
                    return (Lexer::Token(TOK_unary, word));
                }
            } else if (word == "def") {
                return (Lexer::Token(TOK_def, word));
            } else if (word == "set") {
                return (Lexer::Token(TOK_set, word));
            } else if (word == "var") {
                return (Lexer::Token(TOK_var, word));
            } else if (word == "write") {
                return (Lexer::Token(TOK_write, word));
            } else if ((word == "if") || word == "else") {
                return (Lexer::Token(TOK_if, word));
            } else if (word == "while") {
                return (Lexer::Token(TOK_while, word));
            }else if (word == "return") {
                return (Lexer::Token(TOK_return, word));
            }else{
                return Lexer::Token(TOK_identifier, word);
            }

        }

        lastChar = inputText[charIndex];

        if((unsigned int) charIndex == inputText.length()){
            //std::cout << "char index == length" << std::endl;
            return (Lexer::Token());
        }
        /*
        while (!(isspace(lastChar) || lastChar == '\n') && lastChar != EOF) {//skipping any whitespaces
            charIndex++;
            lastChar = inputText[charIndex];
        }
         */
        return (Lexer::Token(TOK_error, "Error no token retreived"));
    }
}

Lexer::Token Lexer::tokenPeek() {
    int prevIndex=charIndex;
    Lexer::Token peek = getNextToken();
    charIndex = prevIndex;
    return (peek);
}

std::string Lexer::Token::toString() {
    std::string result = "<";
    std::string type;
    switch (token_type) {
        case -1: {
            type = "End Of File";
            break;
        }
        case -2: {
            type = "Type";
            break;
        }
        case -3: {
            type = "Boolean";
            break;
        }
        case -4: {
            type = "Integer";
            break;
        }
        case -5: {
            type = "Real";
            break;
        }
        case -6: {
            type = "String";
            break;
        }
        case -7: {
            type = "Identifier";
            break;
        }
        case -8: {
            type = "Multiplication Operation";
            break;
        }
        case -9: {
            type = "Add Operation";
            break;
        }
        case -10: {
            type = "Relational Operation";
            break;
        }
        case -11: {
            type = "Error";
            break;
        }
        case -12: {
            type = "Error Number";
            break;
        }
        case -13: {
            type = "Punctuator";
            break;
        }
        case -14: {
            type = "Def";
            break;
        }
        case -15: {
            type = "Set";
            break;
        }
        case -16: {
            type = "Var";
            break;
        }
        case -17: {
            type = "Write";
            break;
        }
        case -18: {
            type = "If";
            break;
        }
        case -19: {
            type = "While";
            break;
        }
        case -20: {
            type = "Comment";
            break;
        }
        case -21: {
            type = "Unary";
            break;
        }
        case -22: {
            type = "Return";
            break;
        }
    }
    result += type;
    result +=">";

    if(id == ""){
        result += "<";
        result += std::to_string(num);
        result += ">";
    }else if(num == 0){
        result += "<";
        result += id;
        result += ">";
    }else{
        result += "<";
        result += id;
        result += "><";
        result += std::to_string(num);
        result += ">";
    }
    return result;
}
