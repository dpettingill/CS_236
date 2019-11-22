#include "Relation.h"
vector <pair<int, int> > matchingCols;
vector <int> uniqueCols;
bool iai_match_cols;


Relation::Relation() {
    matchingCols.reserve(100);
    uniqueCols.reserve(100);
}


Relation::~Relation(){}


    string Relation::toString(){
        stringstream ss;
        int i = 0;
        for (Tuple t : my_set) {
            //ss << "  ";
            for(Tuple::iterator it = t.begin(); it != t.end(); ++it) {
                if (it == t.begin()) ss << "  ";
                if (it+1 < t.end()) {
                    ss << my_header.at(i) << "=" << t.at(i) << ", "; // of the form N='12345'
                    i++;
                }                 
                else ss << my_header.at(i) << "=" << t.at(i) << "\n";
            }
            
            i = 0; //reset i
            // ss << "\n";
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
        copy.setHeader(my_header);
        copy.setName(my_name);
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

    //when you make a function just to meet lab reqs lol
    Relation Relation::rename(Tuple t) {
        Relation r;
        fillRelation(r);
        r.setHeader(t);
        return r;
    }

    void Relation::setHeader(Tuple t){
        my_header = t;
    }

    void Relation::setName(string name) {
        my_name = name;
    }

    Tuple Relation::getHeader() {
        return my_header;
    }

    int Relation::getSetSize() {
        return my_set.size();
    }

    set<Tuple> Relation::getSet() {
        return my_set;
    }

    // implement natural join - (the major portion of this lab)
//     - join is always possible.
//         - if none of the headers match then we just do a cartesian product
//     - matchingColumns()
//         - go through and find which headers match each other
//         - keep track of these headers in some way (vector of pairs, two diff vectors of ints etc)
//     - findUniqueColumns()
//         - find the unique columns of the 2nd relation
//         - once you have found all of your matching columns then all the rest of the columns must be unique
//         - keep track with a vector of ints
//     - combineColumns()
//     - join (the fun part)
//         for (tuple t1 : in R1)
//             for (tuple t2 : in R2)
//                 if (isJoinable(t1, t2, matchingColumns())) //isJoinable returns a boolean
//                     //combineTuples /*adds in what you already have in the tuple
//                     then add in the tuple information from your unique columns in R2*/
//                     t3 = combineTuples(t, t2, uniqueCols)
//                     resultRelation.add(t3);
//         return resultRelation;
//     isJoinable(t1, t2, vector matchingCols)
//         for each match in matchingCols (vector of pairs of matching columns) {
//            if (t1[matchingCols1] != t2[matchingCols2])
//                 return false;
//         }
//         return true; //if it looped through all of the matching columns and didn't break out returning false then return true
Relation Relation::naturalJoin(Relation r2) {
    Relation result;
    iai_match_cols = false; //if no matching columns exist
    findMatchingCols(r2); //fills up matchingCols and uniqueCols vectors
    //adjust the header and name of result here
    Tuple h_result = combineTuples(my_header, r2.getHeader()); //combine headers
    result.setHeader(h_result); //add them to result
    result.setName("result"); //set the name 
    set<Tuple> set1 = my_set;
    set<Tuple> set2 = r2.getSet();
    for (Tuple t1 : set1) {
        for (Tuple t2 : set2) {
            if (iai_match_cols) { //if we found at least one match
                if (isJoinable(t1, t2)) {
                    Tuple t3 = combineTuples(t1, t2);
                    result.addTuple(t3);
                }
            }
            else { //perform the cartesian product
                Tuple t3 = combTupCartesian(t1, t2); //peforms cartesian product
                result.addTuple(t3);
            }
        }
    }
    matchingCols.clear();
    uniqueCols.clear();
    return result;

}

void Relation::findMatchingCols(Relation r2) {
    Tuple t1 = my_header;
    Tuple t2 = r2.getHeader();
    int i = 0;
    int j = 0;
    bool matched = false;
    for (string s2 : t2) {
        for (string s1 : t1) {
            if (s1 == s2) {
                matchingCols.push_back(make_pair(i,j));
                matched = true;
                iai_match_cols = true; //if we find a match set this to true
            }
            i++;
        }
        if (!matched) uniqueCols.push_back(j); //if the 2nd relation header at j is unique, push it on
        matched = false;
        i = 0;
        j++;
    }
}


//checks all of the matches to see if they have the same information for these tuples
//if they are then we can combine them
bool Relation::isJoinable(Tuple t1, Tuple t2) {
    for (pair<int,int> p : matchingCols) {
        if (t1[p.first] != t2[p.second]) {
            return false;
        }
    }
    return true;
    
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2) {
    int i = 0;
    int size = uniqueCols.size(); //grab every element in t2 that is unique
    while (i < size) {
        t1.push_back(t2.at(uniqueCols.at(i)));
        i++;
    }
    return t1; //this is t3
}


Tuple Relation::combTupCartesian(Tuple t1, Tuple t2) {
    int i = 0;
    int size = t2.size(); //grab every element in t2
    while (i < size) {
        t1.push_back(t2.at(i));
        i++;
    }
    return t1; //this is t3
}

