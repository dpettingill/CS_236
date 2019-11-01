#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(/* args */)
{
}

DatalogProgram::~DatalogProgram()
{
}


void DatalogProgram::addScheme(Predicate my_scheme) {
    schemes_v.push_back(my_scheme);
}

void DatalogProgram::addFact(Predicate my_fact){
    facts_v.push_back(my_fact);
}

void DatalogProgram::addRule(Rule my_rule){
    rules_v.push_back(my_rule);
}

void DatalogProgram::addQuery(Predicate my_query){
    queries_v.push_back(my_query);
}

string DatalogProgram::toString() {
    std::stringstream my_dp_strm;
    int j = schemes_v.size();
    my_dp_strm << "Schemes(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << schemes_v[i].toString(); //calls Predicate toString
    }

    j = facts_v.size();
    my_dp_strm << "Facts(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << facts_v[i].toString(); //calls Predicate toString
    }

    j = rules_v.size();
    my_dp_strm << "Rules(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << rules_v[i].toString(); //calls Predicate toString
    }

    j = queries_v.size();
    my_dp_strm << "Queries(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << queries_v[i].toString(); //calls Predicate toString
    }
    return my_dp_strm.str();
}