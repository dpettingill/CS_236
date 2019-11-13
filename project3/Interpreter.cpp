#include "Interpreter.h"
//part A

Interpreter::Interpreter(DatalogProgram my_data_p)
{
    my_dp = my_data_p; //store datalog program as a data member
    my_schemes = my_dp.getSchemes();
    my_facts = my_dp.getFacts();
    my_queries = my_dp.getQueries();
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
/*For each query in the Datalog program, use a sequence of select, project, and rename operations on the Database to evaluate the query. Evaluate the queries in the order given in the input.

Get the Relation from the Database with the same name as the predicate name in the query.
U
se one or more select operations to select the tuples from the Relation that match the query.
Iterate over the parameters of the query: If the parameter is a constant, 
select the tuples from the Relation that have the same value as the constant
in the same position as the constant. If the parameter is a variable and the
same variable name appears later in the query, select the tuples from the Relation
that have the same value in both positions where the variable name appears.

After selecting the matching tuples, use the project 
operation to keep only the columns from the Relation that
correspond to the positions of the variables in the query.
Make sure that each variable name appears only once in the 
resulting relation. If the same name appears more than once,
keep the first column where the name appears and remove 
\any later columns where the same name appears. 
(This makes a difference when there are other columns 
in between the ones with the same name.)

After projecting, use the rename operation to rename the scheme
 of the Relation to the names of the variables found in the query.
The operations must be done in the order described above: any selects, 
followed by a project, followed by a rename.*/

void Interpreter::decoupleQueries() {
    Relation r;
    map<string, int> mapping;
    string s = "";
    string name = "";
    map<string, int>::iterator it;
    vector<int> toProject;
    int cnt = 0; //keeps track of important tokens in queries ie names, vars and consts
    for (Predicate p: my_queries) { //will perform this on every fact in my_facts
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
        int j = 0;
        while (it != mapping.end()) { //go until you reach the end
            t.at(j) = it->first;
            it++;
            j++;
        }
        r = r.rename(t); //rename r

        mapping.clear(); //clear the map of this query
        name = ""; //reset name
        cnt = 0; //reset cnt

        //output all the things
        ss << r.toString();
    }
}

