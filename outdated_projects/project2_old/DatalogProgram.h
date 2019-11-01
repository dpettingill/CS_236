#pragma once
#include <vector>
#include <stdio.h>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram
{
private:
    /* data */
    vector<Predicate> schemes_v;
    vector<Predicate> facts_v;
    vector<Predicate> queries_v;
    vector<Rule> rules_v;
public:
    DatalogProgram(/* args */);
    ~DatalogProgram();
    void addScheme(Predicate my_scheme);
    void addFact(Predicate my_fact);
    void addRule(Rule my_rule);
    void addQuery(Predicate my_query);
    string toString();
};

