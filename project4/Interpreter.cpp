#include "Interpreter.h"
//globals
Relation r;
unordered_map<string, int> mapping;
unordered_map<string, int>::iterator it;
vector<int> toProject;
vector<Predicate> rule_preds;
int cnt = 0; //keeps track of important tokens in queries ie names, vars and consts

//part A
Interpreter::Interpreter(DatalogProgram my_data_p)
{
    my_dp = my_data_p; //store datalog program as a data member
    my_schemes = my_dp.getSchemes();
    my_facts = my_dp.getFacts();
    my_queries = my_dp.getQueries();
    my_rules = my_dp.getRules();
    rule_preds.reserve(100);
    makeRelations();
    makeTuples();
    //evaluating rules
    joinTestCases();
    //evaluating queries
    // decoupleQueries();
    // cout << ss.str();
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

void Interpreter::joinTestCases() {
    cout << "testing join:\n";
    Relation r1 = my_database.getRelation("snap");
    cout << r1.toString();
    cout << endl;
    Relation r2 = my_database.getRelation("csg");
    cout << r2.toString() << endl;
    Relation result = r1.naturalJoin(r2);
    cout << result.toString() << endl;

    Relation r3 = my_database.getRelation("sl");
    cout << r3.toString() << endl;
    Relation r4 = my_database.getRelation("ncg");
    cout << r4.toString() << endl;
    Relation result2 = r3.naturalJoin(r4);
    cout << result2.toString() << endl;

    cout << "testing join where headers match but no tuple info:\n";
    Relation result3 = r1.naturalJoin(r3);
    cout << result3.toString() << endl;
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
        header.clear();
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


void Interpreter::evaluateRule() {
    int i = 0;
        Relation result;
        for (Predicate p : rule_preds) {
            //treat each body predicate as a query before you join them. bc if you have a constant in the predicate
            // in will shrink your relation significantly and speed up your joins so you finish in time
            
            //check for the head predicate and hold it until the end

            if (i == 0) {
                result = evaluateQuery(p);
            }
            else {
                result = result.naturalJoin(evaluateQuery(p)); //evaluates and joins it to your result
            }
            i++;
        }
        // findProjectCols() //gets the columns to project from headPredicate
        // result = result.project()
        // result = result.rename();
        // result = dB[headPredicate.name()].unionize(result);
}

void Interpreter::evaluateRules() {
    for (Rule rule : my_rules) {
        rule_preds = rule.getPreds();
        evaluateRule();
        rule_preds.clear();
    }
}
