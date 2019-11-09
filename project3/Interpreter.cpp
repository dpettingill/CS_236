#include "Interpreter.h"
//part A

Interpreter::Interpreter(DatalogProgram my_data_p)
{
    my_dp = my_data_p; //store datalog program as a data member
    my_schemes = my_dp.getSchemes();
    my_facts = my_dp.getFacts();
    makeRelations();
    makeTuples();
    cout << my_database.toString();
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
            else my_tuple.push_back(f.getToken(i).getTokenString()); //otherwise it is contents of the fact
        }
        //you need to find the appropriate relation here in the map
        //add the tuple to that relation
        // cout << name << ": ";
        // for (string s : my_tuple) {
        //     cout << s;
        // }
        // cout << endl;
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
            else header.push_back(s.getToken(i).getTokenString()); //all other tokens get added to the tuple
        }
        Relation my_rel = Relation(name, header);
        my_database.addRelation(name, my_rel);
    }
}


//part B
