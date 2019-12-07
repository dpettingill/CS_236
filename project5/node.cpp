#include "node.h"
node::node(Rule rule, int n_id) {
    node_id = n_id;
    my_rule = rule;
    visited = false;
}
node::~node(){}

void node::insert_dependency(int id) {
    friend_nodes.insert(id);
}

string node::depend_toString() {
    stringstream ss;
    unsigned int i = 0;
    for (int id : friend_nodes) {
        if (i == friend_nodes.size()-1) ss << "R" << id;
        else ss << "R" << id << ",";
        i++;
    }
    return ss.str();
}

void node::insert_rev_dep(int id) {
    rev_friend_nodes.insert(id);
}

string node::revDepend_toString() {
    stringstream ss;
    unsigned int i = 0;
    for (int id : rev_friend_nodes) {
        if (i == rev_friend_nodes.size()-1) ss << "R" << id;
        else ss << "R" << id << ",";
        i++;
    }
    return ss.str();
}

bool node::isVisited() {
    return visited;
}

void node::descend(int i) {
    if (i == 0) set<int>::iterator it = friend_nodes.begin();
    else if (i == 1) set<int>::iterator it = rev_friend_nodes.begin();
    else cout << "something is wrong\n";
    for (int id : rev_friend_nodes) {

    }
}
