#include "Relation.h"

// Relation::Relation(string name, Tuple header)
// {
//     my_name = name;
//     my_header = header;
// }

Relation::Relation() {}


Relation::~Relation()
{
}


    string Relation::toString(){
        stringstream ss;
        //header toString();
        ss << "Header = ( ";
        for (string s: my_header) {
            ss << s << ", ";
        }
        ss << ")\n";
        for (Tuple t : my_set) {
            ss << "Tuple = ( ";
            //tuple toString()
            for (string s : t) {
                ss << s << ", "; // of the form N='12345'
            }
            ss << ")\n";
        }
        return ss.str();
}

    void Relation::addTuple(Tuple my_tuple) {
        my_set.insert(my_tuple);
    }


    void Relation::fillRelation(Relation& r) {
        r.my_name = my_name;
        r.my_header = my_header;
        for (Tuple t: my_set) {
            r.addTuple(t);
        }
    }

    Relation Relation::select(int col, string val) {
        Relation copy;
        for (Tuple t : my_set) {
            if (t.at(col) == val) {
                copy.my_set.insert(t);
            }
        }
        return copy;
    }

    Relation Relation::select(int col1, int col2) {
        Relation copy;
        copy.setHeader(my_header);
        copy.setName(my_name);
        for (Tuple t : my_set) {
            if (t.at(col1) == t.at(col2)) {
                copy.my_set.insert(t); //erases the element from the relation
            }
        }
        return copy;
    }

    Relation Relation::project(vector<int> toProject) {
        Relation copy;
        Tuple copy_t;
        copy.setName(my_name); //get move the name over
        for (int i : toProject) {
            copy_t.push_back(my_header.at(i));
        }
        copy.setHeader(copy_t); //set the copied r's new header
        copy_t.clear(); //clear to fill the set below
        for (Tuple t: my_set) {
            for (int i : toProject) {
                copy_t.push_back(t.at(i)); //put the string in t at pos i in new tuple "copy_t"
            } 
            copy.addTuple(copy_t);  //fill up copy relation with new tuples
            copy_t.clear(); //clear the copy_t after each iteration 
        }
        return copy;
    }
    void Relation::setHeader(Tuple t){
        my_header = t;
    }

    void Relation::setName(string name) {
        my_name = name;
    }