#include "Database.h"
Database::Database(/* args */)
{
}

Database::~Database()
{
}

void Database::addTuple(string name, Tuple t) {
    //trys to get the relation with name
    //adds a Tuple to that relation
    my_map.at(name).addTuple(t);
}

void Database::addRelation(string name, Relation r) {
    my_map.insert(pair<string, Relation>(name, r));
}

string Database::toString() {
    stringstream ss;
    map<string, Relation>::iterator it = my_map.begin();
    while (it != my_map.end()) {
        Relation r = it->second;
        ss << r.toString();
        it++;
    }
    return ss.str();
}

Relation Database::getRelation(string name) {
    return my_map.at(name);
}

void Database::eraseRelation(string name) {
    my_map.erase(name);
}

int Database::findPreCount() {
    int count = 0;
    map<string, Relation>::iterator it = my_map.begin();
    while (it != my_map.end()) {
        Relation r = it->second;
        set<Tuple> rSet = r.getSet();
        for (Tuple t : rSet) {
            count++;
        }
        it++;
    }
    return count;
}

int Database::findPostCount() {
    int count = 0;
    map<string, Relation>::iterator it = my_map.begin();
    while (it != my_map.end()) {
        Relation r = it->second;
        set<Tuple> rSet = r.getSet();
        for (Tuple t : rSet) {
            count++;
        }
        it++;
    }
    return count;
}

