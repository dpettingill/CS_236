#pragma once
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Tuple.h"
#include <stdio.h>
#include <unordered_map>
#include "graph.h"
using namespace std;

class Interpreter
{
private:
    DatalogProgram my_dp;
    Database my_database;
    vector<Predicate> my_facts;
    vector<Predicate> my_schemes;
    vector<Predicate> my_queries; //use this for final output
    vector<vector<string>> queries; //use this for evaluating not the final output 
    vector<Rule> my_rules;
    stringstream ss; //for printing out the final output
public:
    Interpreter(DatalogProgram my_data_p);
    ~Interpreter();
    void project4();
    void project5();
    void testCases();
    void joinTestCases();
    void evalRuleTestCases();
    void makeTuples();
    void makeRelations();
    void decoupleQueries();
    Relation evaluateQuery(Predicate p, bool rule_eval);
    void evaluateRule(vector<Predicate> preds);
    Relation evaluateRule(vector<Predicate> preds, Relation r); //test version
    void evaluateRules();
    void findProjectCols(Predicate p, Relation r);
    void evalRulesGraph();
    void output_sccs(map<int, vector<node>>::reverse_iterator it);
};



//Datalog -> Interpreter -> Database
//this takes in a datalog and looks at it, breaks it up and adds those things to the database
//in the constructor store the DatalogProgram as a data member
// Make a relation for each scheme predicate, and put that relation in the database data member
// make a tuple for each fact predicate, and put that tuple in the appropriate relatoin in the database
//converting facts into tuples
// facts contain a vector of strings -> put that into a tuple
// then put that tuple into the relation that corresponds to the fact name

// converting a scheme into a relation
// take the name of the scheme and make it the name of the relation
// we take the info in the scheme and put that into a tuple that becomes the header of the relation
// relation has string name
//              tuple header
//              set<tuple> rows

//for the interpreter there are assumptions that you get to make
//they will not be giving us any "funny business"


//interpreting queries
//you will run a similar for(Query : myQueries) loop to go through all the queries
//returns new relations. Does not modify the old ones
// something like people(same, same) ? (A, B) is looking at columns A and B in a relation people
// and checks to see if the things in A are the same as the things in B

//constants are strings, variables don't have the apostrophes
//vars
//map<string, int>
//toProject
//vector<int>
//newHeader
//Tuple

//use the map to know if we have seen the variable before
//look at the flowchart in the thing
