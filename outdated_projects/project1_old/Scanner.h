/*
Scanner needs to:
- read from the input file
- Store tokens for later use
- Keep track of the curren line number


*constructor takes the file name as a string
* another function should read through the file na dmake all the tokens
* tou can have as many other functions as you need
*/
#pragma once
#include <iostream>
#include <fstream>
#include "Token.h"
#include <vector>
#include <string>

enum scan_st {new_char_st, id_st, colon_st, string_st, comment_st, block_comment_st};

class Scanner{
    private:
    std::string filename;
    public:
    Scanner(std::string fn) { //constructor
        filename = fn;
    } 
    ~Scanner() {} //deconstructor
    void readFile();
    void tokenize();
    void receivedChar();
    void keywordComp();
    void setTokenVals(TokenType tok_type, std::string tok_str, int lin_num);
    void printTokenVector();
};