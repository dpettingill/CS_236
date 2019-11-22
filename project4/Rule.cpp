#include "Rule.h"

Rule::Rule(/* args */)
{
}

Rule::~Rule()
{
}

void Rule::addPredicate(Predicate my_p) {
    my_rule_of_preds.push_back(my_p);
}

std::string Rule::toString() {
    std::stringstream rule_strm;
    int j = my_rule_of_preds.size();
    for (int i = 0; i < j; i++) {
        if (my_rule_of_preds.at(i).getType() == head) {
            rule_strm << my_rule_of_preds.at(i).toString() << " :- ";
        }
        else if (i != (j-1)) rule_strm << my_rule_of_preds.at(i).toString() << ", ";
        else rule_strm << my_rule_of_preds.at(i).toString() << endl;
    }
    return rule_strm.str();
}

vector<Predicate> Rule::getPreds() {
    return my_rule_of_preds;
}