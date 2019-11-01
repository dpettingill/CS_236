#pragma once
#include "Token.h"
#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;

enum predType {Scheme, Fact, Query, head, body};

class Predicate
{
private:
    vector<Token> pred_tokens;
    int length;
    predType type;


public:
    Predicate(vector<Token> toks, int l, predType t);
    ~Predicate();
    std::string toString(); //maybe make this a string
    predType getType();
};


