#include "Token.h"

//data members
//token_type, token_string, line_number

std::string TokenTypeToString(TokenType my_token_type) {

    switch(my_token_type) {
        case COMMA: return "COMMA"; break;
        case PERIOD: return "PERIOD"; break;
        case Q_MARK:  return "Q_MARK"; break;
        case LEFT_PAREN: return "LEFT_PAREN"; break;
        case RIGHT_PAREN: return "RIGHT_PAREN"; break;
        case COLON: return "COLON"; break;
        case COLON_DASH: return "COLON_DASH"; break;
        case MULTIPLY: return "MULTIPLY"; break;
        case ADD: return "ADD"; break;
        case SCHEMES: return "SCHEMES"; break;
        case FACTS: return "FACTS"; break;
        case RULES: return "RULES"; break;
        case QUERIES: return "QUERIES"; break;
        case ID: return "ID"; break;
        case STRING: return "STRING"; break;
        case COMMENT: return "COMMENT"; break;
        case UNDEFINED: return "UNDEFINED"; break;
        case ENDFILE: return "EOF"; break;
    }
    return "something wrong happen\n";
}

std::string Token::toString() { //takes the data members and outputs them as a string (token_type, token_string, line_number)
    std::stringstream my_token_stream;
    //call ttts function here to get string version of tokentype
    my_token_stream << "(" << TokenTypeToString(token_type) << ",\"" << token_string <<  "\"," << line_number << ")\n";
    return my_token_stream.str();
}


TokenType Token::getTokenType() {
    return token_type;
}

void Token::setTokenType(TokenType new_type) {
    token_type = new_type;
}

void Token::setTokenString(std::string new_string) {
    token_string = new_string;
}

 void Token::setLineNum(int ln){
     line_number = ln;
 }
 
