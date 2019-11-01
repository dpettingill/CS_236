#pragma once
#include "Token.h"
#include <vector>
#include "DatalogProgram.h"
#include "stdio.h"
#include "Predicate.h"
#include "Rule.h"
#include <stdbool.h>

using namespace std;
class Parser
{
private:
    vector<Token> parser_tokens;
    int vect_pos;
    DatalogProgram my_dp;
    /* data */
public:
    Parser(vector<Token> tokens);
    ~Parser();
    void parse();
    void match(TokenType match_token_type);
    TokenType peekNextTokenType();
    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate(Rule& my_r);
    void parsePredicate(Rule& my_r); //definition for rule
    void parsePredicate(); //definition for query
    void parsePredicateList(Rule& my_r);
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();
    void parseExpression();
    void parseOperator();
    void printTokenVector();
    Predicate new_pred(predType my_type);
};



//take in vector of tokens
// for every production you should make one function
// create an int in parser class that tells you what position you are in the token vector
// for every terminal check to see if it is the right type
// if it is not the right type then throw an exception
// for every nonterminal call that function

// have a match function
// eg for fact production
// match (ID)
// match(left_paren)
// match(String)
// parseStringList()
//match (R_Paren)
// match(PERIOD)



// you have a try function at the beginning of your parse program
// a throw statement is helpful b/c no matter how deep into functions you are it will leave and go to the nearest catch statement
// catch statements go within your try statement
// throw the token that was not what you expected


// match function
// if the token matches the token you were expecting then advance
// else throw that token

//if a nonterminal has more than one production
// figure out the first and follow sets
// then if (nextToken) is a terminal in the first set
// then do "Scheme schemeList"
// else do the lambda
// which means it does nothing aka ends the recurrsion

// at first try to just go through checking for success or failure

//we want to hold the data that we parse
// in the predicate class
// we hold the name
// and the list of parameters
// rules have predicates inside of them
// will have a string with a vector of parameters



// an expression has a left parameter an operator then a right parameter
//one of the productions is the definition of a parameter
// one of the productions is the definition of an expression

//all of the toStrings call each other until we get to a predicate, parameter or an expression
// then it just prints itself out at that point
// all of these things will print to the "set"
// the set will hold everything until the end and then print them all out
// it will also optimize and remove any duplicates

//for part two 
// instead of the parse functions just returning success vs failure
// now they will return what they are parsing
// eg void parseFact() becomes predicate parseFact()
// returning an object of the type predicate


//figure out what polymorphism is
// ask Haylee cause she knows pokemon || google it
// something something something