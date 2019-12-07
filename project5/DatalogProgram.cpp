#include "DatalogProgram.h"
static stringstream my_ss;


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

void DatalogProgram::Domain() {
    
    int j = facts_v.size();
    
    //first grab all of the strings individually
    for (int i = 0; i < j; i++) {
        int k = facts_v.at(i).vector_size();
        for (int l = 0; l < k; l++) {
            TokenType tt = facts_v.at(i).getToken(l).getTokenType();
            //cout << tt;
            if (tt == STRING) {
                domain_v.push_back(facts_v.at(i).getToken(l).getTokenString());
            }
        }
    }

    //now get rid of duplicates and sort
    vector<std::string> facts = domain_v;
    std::sort(facts.begin(), facts.end()); //sort the strings    
    int size = facts.size();
    for (int i = 0; i < (size - 1); i++) {
        //check for duplicates
        if (facts.at(i) == facts.at(i+1)) {
            //push that element to the back
            for (int h = i; h < (size-1); h++) {
                std::string dummy = facts.at(h+1);
                facts.at(h+1) = facts.at(h);
                facts.at(h) = dummy;
            }
            facts.pop_back();
            size--;
        }
    }
    my_ss << "Domain(" << size << "):\n";
    for (int i = 0; i < size; i++) {
        my_ss << "  " << facts[i] << endl;
    }   
}

string DatalogProgram::toString() {
    std::stringstream my_dp_strm;

    //schemes stuff
    int j = schemes_v.size();
    my_dp_strm << "Schemes(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << schemes_v[i].toString(); //calls Predicate toString
    }

    //facts stuff
    j = facts_v.size();
    my_dp_strm << "Facts(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << facts_v[i].toString(); //calls Predicate toString
    }

    //rules stuff
    j = rules_v.size();
    my_dp_strm << "Rules(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << rules_v[i].toString(); //calls Predicate toString
    }

    //query stuff
    j = queries_v.size();
    my_dp_strm << "Queries(" << j << "):\n";
    for (int i = 0; i < j; i++)
    {
        my_dp_strm << "  " << queries_v[i].toString(); //calls Predicate toString
    }

    //domain stuff
    Domain();
    j = domain_v.size();
    my_dp_strm << my_ss.str();

    return my_dp_strm.str();
}

    vector<Predicate> DatalogProgram::getFacts(){
        return facts_v;
    }
    vector<Predicate> DatalogProgram::getSchemes(){
        return schemes_v;
    }
    vector<Predicate> DatalogProgram::getQueries(){
        return queries_v;
    }
    vector<Rule> DatalogProgram::getRules(){
        return rules_v;
    }