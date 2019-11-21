#pragma once
#include <stdio.h>
#include <iostream>
#include<string>
#include <algorithm>
#include <sstream>
#include<set>
#include<vector>
#include "Tuple.h"
using namespace std;

class Relation
{
private:
    /* data */
    string my_name;
    Tuple my_header;
    set<Tuple> my_set;


public:
    //Relation(string name, Tuple header);
    Relation();
    ~Relation();
    string toString();
    void addTuple(Tuple my_tuple);
    void fillRelation(Relation& r);
    Relation select(int col, string val);
    Relation select(int col1, int col2);
    Relation project(vector<int> toProject);
    Relation rename(Tuple t);
    Tuple getHeader();
    int getSetSize();
    void setHeader(Tuple t);
    void setName(string name);
    set<Tuple> getSet();
};



//When you create a relation you give it a name and a header
//create a function where you can add in tuples
// relation has string name
//              tuple header
//              set<tuple> rows



/*for(Tuple t: mySet) {
    It will perform this loop on every Tuple that is in mySet.
    cout << Tuple.toString();
}*/

// Relation
// select(int col, string val) //create a new relation where the specified column has the specified value
// select(int col1, int col2) //this enforces that value at col1 is the same as the value at col2
//myNewRelation = myRelation.select(approp. params);
// project(vector<int> toProject) //r2 = r1.project(<2,0>) //this says I want col 2 and then col 0
//rename(Tuple t) //don't need to implement for this lab


