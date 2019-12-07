#include "graph.h"
graph::graph(vector<Rule> rules) {
    my_rules = rules;
    assign_nodes();
    create_dependencies();
    print_dependencies();
    print_revDependencies();
}
graph::~graph(){}

void graph::assign_nodes() {
    for (unsigned i = 0; i < my_rules.size(); i++) {
        node my_node(my_rules.at(i), i);
        node_graph.insert(pair<int, node>(i, my_node));
    }
}

void graph::create_dependencies() {
    vector<Predicate> my_preds;
    for (unsigned i = 0; i < my_rules.size(); i++) {
        my_preds = my_rules.at(i).getPreds();
        //what if I get all of the predicates for each rule
        //then run a for loop to compare those preds to each
        //of the head preds
        for (unsigned j = 1; j < my_preds.size(); j++) {
            for (unsigned k = 0; k < my_rules.size(); k++) {
                if (my_preds.at(j).getToken(0).getTokenString() == my_rules.at(k).getHeadPred().getToken(0).getTokenString()) {
                    //then we found a dependency and add it to the node at id i
                    node_graph.find(i)->second.insert_dependency(k); //find the node corresponding to the rule we are looking at
                    node_graph.find(k)->second.insert_rev_dep(i); //builds our reverse dep graph
                }
            }
        }
    }
}

void graph::print_dependencies() {
    stringstream ss;
    map<int, node>::iterator it = node_graph.begin();
    while (it != node_graph.end()) {
        ss << "R" << it->first << ":";
        ss << it->second.depend_toString() << endl;
        it++;
    }
    cout << "Dependency Graph\n";
    cout << ss.str();
}

void graph::print_revDependencies() {
    stringstream ss;
    map<int, node>::iterator it = node_graph.begin();
    while (it != node_graph.end()) {
        ss << "R" << it->first << ":";
        ss << it->second.revDepend_toString() << endl;
        it++;
    }
    cout << "Reverse Dependency Graph\n";
    cout << ss.str();
}

void graph::dfs() {

}

void graph::dfs_rev() {
    /*
    iterate through our graph
    if (visited) //do nothing
    else {
        //seems like this should be a recursive function
        //passes in a pointer to the node
        descend() {
            for (int id : rev_friend_nodes) {
                node* tmp = graph.find(id)->second;
                if (*tmp.isVisited()) //do nothing
                else {
                    &tmp.descend(tmp); //recursive funct
                }
            }
            visited = true;
        }
    }
    i++
    */

   map<int, node>::iterator it = node_graph.begin();
   while (it != node_graph.end()) {
       it++;
   }
}