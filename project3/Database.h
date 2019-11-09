#pragma once
#include <map>
#include <string>
#include "Relation.h"
#include <stdio.h>
using namespace std;

class Database
{
private:
    /* data */
    map<string, Relation> my_map; //string identifiers, holds Relations

public:
    Database(/* args */);
    ~Database();
    void addTuple(string name, Tuple t);
    void addRelation(string name, Relation r);
    string toString();
};



//Datalog -> Database
//how to access a relation based off of it's name
//#include <map>
//declaring a map
// map<string, Relation> myMap
// a map is like a vector or an array
// but with vectors and arrays you can only access with an int
// with a map you get to pick what type you can access it with
// here we are using string as our accessor. 
// myMap["x"] = myRelation;
// so then "x" becomes the key to accessing myRelation
// for us the key will become the name of the relation.