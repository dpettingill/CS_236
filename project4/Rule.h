#pragma once
#include "Predicate.h"

class Rule
{
private:
    /* data */
    vector<Predicate> my_rule_of_preds;
public:
    Rule(/* args */);
    ~Rule();
    void addPredicate(Predicate my_p);
    std::string toString();
    vector<Predicate> getPreds();
};


