#ifndef _SCANNER_H_
#define _SCANNER_H_


//#pragma once
#include <iostream>
#include <fstream>
#include "Token.h"
#include <vector>

enum scan_st {new_char_st, id_st, colon_st, string_st, comment_st, block_comment_st};

class Scanner{
    private:
    std::string filename;
    public:
    Scanner(); //constructor
    ~Scanner(); //deconstructor
    void readFile();
    void tokenize(char rc);
    void receivedChar(char rc);
    void keywordComp();
    void setTokenVals(TokenType tok_type, std::string tok_str, int lin_num);
    void setFilename(std::string fn);
    void printTokenVector();
};
#endif