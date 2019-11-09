#include "Relation.h"

Relation::Relation(string name, Tuple header)
{
    my_name = name;
    my_header = header;
}

Relation::Relation() {}


Relation::~Relation()
{
}


string Relation::toString(){
    stringstream ss;
    //header toString();
    ss << "Header = ";
    for (string s: my_header) {
        ss << s;
    }
    ss << endl;
    for (Tuple t : my_set) {
        ss << "Tuple = ";
        //tuple toString()
        for (string s : t) {
            ss << s; // of the form N='12345'
        }
        ss << endl;
    }
    return ss.str();
}

void Relation::addTuple(Tuple my_tuple) {
    my_set.insert(my_tuple);
}


    void Relation::select(Relation& r, int col, string val) {
        //set<Tuple>::iterator setIt = r.my_set.begin();
        for (Tuple t : r.my_set) {
            if (t.at(col) != val) {
                //r.    my_set.erase(setIt); //erases the element from the relation
                r.my_set.erase(t);
            }
            //setIt++;
        }
        if (r.my_set.empty()) cout << "We couldn't find that thing\n";
    }

    void Relation::select(Relation& r, int col1, int col2) {
        for (Tuple t: r.my_set) {
            if (t.at(col1) != t.at(col2)) {
                r.my_set.erase(t); //erases the element from the relation
            }
        }
        if (r.my_set.empty()) cout << "We couldn't find that thing\n";
    }
    void Relation::project(Relation& r, vector<int> toProject) {
        Relation copy_r;
        Tuple copy_t;
        copy_r.my_name = r.my_name; //get move the name over
        for (int i : toProject) {
            copy_t.push_back(r.my_header.at(i)); //create our new header
        }
        copy_r.my_header = copy_t; //sets the header for copy_r
        copy_t.clear(); //clears in prep for filling the tuples of copy_r
        for (Tuple t: r.my_set) {
            for (int i : toProject) {
                copy_t.push_back(t.at(i)); //put the string in t at pos i in new tuple "copy_t"
            } 
            copy_r.addTuple(copy_t);  //fill up copy relation with new tuples
            copy_t.clear(); //clear the copy_t after each iteration 
        }

        r = copy_r; //Can we do this?
        if (r.my_set.empty()) cout << "We couldn't find that thing\n";
    }
    void Relation::rename(Relation& r, Tuple t){
        r.my_header = t;
    }