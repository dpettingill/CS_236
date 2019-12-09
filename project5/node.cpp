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

set<int> node::getFriendNodes() {
    return friend_nodes;
}

set<int> node::getFriendNodes_rev() {
    return rev_friend_nodes;
}

void node::markVisited() {
    visited = true;
}

void node::markNotVisited() {
    visited = false;
}

void node::setPostOrder(int po) {
    post_order = po;
}

int node::getId() {
    return node_id;
}

int node::getPostOrder() {
    return post_order;
}