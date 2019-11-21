#include "Interpreter.h"
//globals
Relation r;
unordered_map<string, int> mapping;
unordered_map<string, int>::iterator it;
vector<int> toProject;
vector <pair<int, int> > matchingCols;
vector <int> uniqueCols;
int cnt = 0; //keeps track of important tokens in queries ie names, vars and consts
bool iai_match_cols;

//part A
Interpreter::Interpreter(DatalogProgram my_data_p)
{
    my_dp = my_data_p; //store datalog program as a data member
    my_schemes = my_dp.getSchemes();
    my_facts = my_dp.getFacts();
    my_queries = my_dp.getQueries();
    matchingCols.reserve(100);
    uniqueCols.reserve(100);
    makeRelations();
    makeTuples();
    decoupleQueries();
    cout << ss.str();
}

void Interpreter::testCases() {
    //testing stuff
    cout << "testing select\n";
    string name = "SK";
    Relation r = my_database.getRelation(name);
    int col = 0;
    string val = "'b'";
    Relation r2 = r.select(col, val);
    cout << r2.toString();
    int col1 = 0;
    int col2 = 1;
    Relation r3 = r.select(col1,col2);
    cout << r3.toString();
    //testing project
    vector<int> vect{0};
    Relation r4 = r.project(vect);
    cout << r4.toString();
    vector<int> vect1{1};
    Relation r5 = r.project(vect1);
    cout << r5.toString();
}

// Predicate my_p(tok_vec, length, my_type);//create a new predicate
//destructor
Interpreter::~Interpreter() {}

//will pull out all of the facts and turn them into tuples
void Interpreter::makeTuples(){
    //add the newly created Tuples to the relation set
    string name;
    Tuple my_tuple = Tuple();
    for (Predicate f: my_facts) { //will perform this on every fact in my_facts
        //cout << f.toString(); //this doesn't make sense
        for (int i = 0; i < f.vector_size(); i++) {
            if (i==0) name = f.getToken(i).getTokenString(); //grab first token string as name
            else if (f.getToken(i).getTokenString() == ".") {} //get rid of periods
            else if (f.getToken(i).getTokenString() == ",") {} //get rid of commas
            else if (f.getToken(i).getTokenString() == "(") {} //get rid of (s
            else if (f.getToken(i).getTokenString() == ")") {} //get rid of )s
            else my_tuple.push_back(f.getToken(i).getTokenString()); //otherwise it is contents of the fact
        }
        
        my_database.addTuple(name, my_tuple);
        my_tuple.clear();
    }
   
    
}

void Interpreter::makeRelations() {
    //pull out all the schemes
    //add the newly created relations to the database map
    //need to figure out the relation name and header before declaring it.
    //I think we just want to add our name and header directly to the new relation
    string name = "";
    Tuple header = Tuple();
    for (Predicate s: my_schemes) {
        for (int i = 0; i < s.vector_size(); i ++) {
            if (i==0) name = s.getToken(i).getTokenString(); //first token is name of scheme
            else if (s.getToken(i).getTokenString() == "(") {} //get rid of (s
            else if (s.getToken(i).getTokenString() == ",") {} //get rid of commas
            else if (s.getToken(i).getTokenString() == ")") {} //get rid of )s
            else header.push_back(s.getToken(i).getTokenString()); //all other tokens get added to the tuple
        }
        Relation my_rel = Relation();
        my_rel.setHeader(header);
        my_rel.setName(name);
        my_database.addRelation(name, my_rel);
    }
}


//part B
void Interpreter::evaluateQuery(Predicate p) {
    string s = "";
    string name = "";
    for (int i = 0; i < p.vector_size(); i++) {
        s = p.getToken(i).getTokenString();
        ss << s; //get the query stuff
        //select based on the query
        if (i == 0) {
            name = p.getToken(i).getTokenString(); //name is query.at(0)
            r = my_database.getRelation(name); 
            //don't increment cnt in here, name isn't a column
        }
        else if (p.getToken(i).getTokenType() == ID) {
            //variable
            it = mapping.find(s); //look to see if this token has already been seen
            if (it != mapping.end()) { //found the element
                int col2 = it->second; 
                r = r.select(cnt, col2); //run select2
                cnt++; //important token seen, increment
            }
            else {
                //mark it for project and rename
                mapping.insert(pair<string, int>(s,cnt)); //put the string and pos in map
                toProject.push_back(cnt); //grab columns here
                cnt++; //important token seen, increment
            }
        }
        else if (p.getToken(i).getTokenType() == STRING) {
            //constant
            r = r.select(cnt,s); //run select1
            cnt++; //important token seen, increment
        }
        s = ""; //reset s  
    }
}

void Interpreter::decoupleQueries() {
    mapping.reserve(1000); //initialize this to something huge so it doesn't resize and jumble everything up
    for (Predicate p: my_queries) { //will perform this on every fact in my_facts
          evaluateQuery(p);
               
        //yes/no
        int size = r.getSetSize();
        if (size > 0) {
            ss << " Yes(" <<  size << ")\n";
        }
        else {
            ss << " No\n";
        }

        //project
        r = r.project(toProject); //project the columns you grabbed earlier
        toProject.clear();
        //rename
        it = mapping.begin(); //put an iterator to the map beginning
        Tuple t = r.getHeader(); //get the current header
        int j;
        j = t.size()-1;
        // int j = 0;
        while (it != mapping.end()) { //go until you reach the end
            t.at(j) = it->first;
            it++;
            j--;
        }
        r = r.rename(t); //rename r
        mapping.clear(); //clear the map of this query
        cnt = 0; //reset cnt

        //output all the things
        ss << r.toString();
    }
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
void Interpreter::naturalJoin(Relation r1, Relation r2) {
    Relation result;
    iai_match_cols = false; //if no matching columns exist
    findMatchingCols(r1, r2); //fills up matchingCols and uniqueCols vectors
    //adjust the header and name of result here
    if (iai_match_cols) { //if we found at least one match
        set<Tuple> set1 = r1.getSet();
        set<Tuple> set2 = r2.getSet();
        for (Tuple t1 : set1) {
            for (Tuple t2 : set2) {
                if (isJoinable(t1, t2)) {
                    Tuple t3 = combineTuples(t1, t2);
                    result.addTuple(t3);
                }
            }
        }
    }
    else { //perform the cartesian product

    }

}

void Interpreter::findMatchingCols(Relation r1, Relation r2) {
    Tuple t1 = r1.getHeader();
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
bool Interpreter::isJoinable(Tuple t1, Tuple t2) {
    for (pair<int,int> p : matchingCols) {
        if (t1[p.first] != t2[p.second]) {
            return false;
        }
    }
    return true;
    
}

Tuple Interpreter::combineTuples(Tuple t1, Tuple t2) {
    int i = 0;
    int size = t2.size();
    while (i < size) {
        t1.push_back(t2.at(uniqueCols.at(i)));
        i++;
    }
    return t1; //this is t3
}
