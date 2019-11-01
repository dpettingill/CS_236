#include "Predicate.h"

Predicate::Predicate(vector<Token> toks, int l, predType t)
{
    pred_tokens = toks;
    length = l;
    type = t;
}

Predicate::~Predicate()
{
}

std::string Predicate::toString() {
    //do stuff here
    std::stringstream my_token_stream;
    int j = pred_tokens.size();
    for (int i = 0; i < j; i++)
    {   
        if (i == (j-1) && (type != head && type != body)) { //last token
            my_token_stream << pred_tokens[i].getTokenString() << endl; 
        }
        else my_token_stream << pred_tokens[i].getTokenString(); 
    }
    return my_token_stream.str();
}

predType Predicate::getType() {
    return type;
}