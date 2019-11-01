#pragma once
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

enum TokenType {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDFILE};

class Token {
    private:
    std::string token_string;
    int line_number;
    TokenType token_type;

    public: 
    Token() {}//constructor
    ~Token() {} //deconstructor
    std::string toString(); //print out (token_type, token_string, line_number)
    TokenType getTokenType();
    void setTokenType(TokenType new_type);
    void setTokenString(std::string new_string);
    void setLineNum(int ln);
    
};

