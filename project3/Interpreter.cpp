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
/*For each query in the Datalog program, use a sequence of select, project, and rename operations on the Database to evaluate the query. Evaluate the queries in the order given in the input.

Get the Relation from the Database with the same name as the predicate name in the query.
Use one or more select operations to select the tuples from the Relation that match the query. Iterate over the parameters of the query: If the parameter is a constant, select the tuples from the Relation that have the same value as the constant in the same position as the constant. If the parameter is a variable and the same variable name appears later in the query, select the tuples from the Relation that have the same value in both positions where the variable name appears.
After selecting the matching tuples, use the project operation to keep only the columns from the Relation that correspond to the positions of the variables in the query. Make sure that each variable name appears only once in the resulting relation. If the same name appears more than once, keep the first column where the name appears and remove any later columns where the same name appears. (This makes a difference when there are other columns in between the ones with the same name.)
After projecting, use the rename operation to rename the scheme of the Relation to the names of the variables found in the query.
The operations must be done in the order described above: any selects, followed by a project, followed by a rename.*/

void Interpreter::evaluateQueries() {
    
}
