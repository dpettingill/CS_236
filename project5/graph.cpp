#include "graph.h"
graph::graph(vector<Rule> rules) {
    my_rules = rules;
    post_order = 1;
    assign_nodes();
    create_dependencies();
    print_dependencies();
    cout << endl;
    print_revDependencies();
    cout << endl;
    dfs();
    dfs_rev();
    output_sccs();
    cout << endl;
    output_pos();
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
   map<int, node>::iterator it = node_graph.begin();
   while (it != node_graph.end()) {
       node* tmp = &it->second;
       if (tmp->isVisited()) {} //do nothing
       else {
           descend(tmp);
       }
       it++;
   }
   clear_visits(); //clear the visited var of the nodes
}

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

   //how do I want to implement sccs? a vector<vector<node>>?
   //what if I pass in a vector<node> into the descend function everytime I call it
   //then as long as I keep descending it will add those nodes to that vector
   //and when I exit in the dfs_rev func I can add that vector to my_sccs
   //and I need to keep track of post-order numbers, how should I do that?
   //do I make it a node data member?
   //ok but when do I assign it? at the end of descend!
void graph::dfs_rev() {
   map<int, node>::iterator it = node_graph.begin();
   vector<node> scc;
   while (it != node_graph.end()) {
       node* tmp = &it->second;
       if (tmp->isVisited()) {} //do nothing
       else {
           descend_rev(tmp, scc);
           my_sccs.push_back(scc);
           scc.clear();
       }
       it++;
   }
   clear_visits(); //clear the visited var of the nodes
}


void graph::descend_rev(node* tmp, vector<node> &scc) {
    // cout << "descend:" << post_order << endl;
    set<int> my_nodes;
    tmp->markVisited();
    my_nodes = tmp->getFriendNodes_rev();
    for (int id : my_nodes) {
        node* tmp2 = &node_graph.find(id)->second;
        if (tmp2->isVisited()) {} //do nothing
        else descend_rev(tmp2, scc);
    }
    scc.push_back(*tmp);
    return;
}

void graph::descend(node* tmp) {
    // cout << "descend:" << post_order << endl;
    set<int> my_nodes;
    tmp->markVisited();
    my_nodes = tmp->getFriendNodes();
    for (int id : my_nodes) {
        node* tmp2 = &node_graph.find(id)->second;
        if (tmp2->isVisited()) {} //do nothing
        else descend(tmp2);
    }
    tmp->setPostOrder(post_order);
    post_order++;
    return;
}

void graph::output_sccs() {
    cout << "SCCs\n";
    for (unsigned i = 0; i < my_sccs.size(); i++) {
        cout << "SCC:" << i << " ";
        for (unsigned j = 0; j < my_sccs.at(i).size(); j++) {
            if (j+1 == my_sccs.at(i).size())
            cout << "R" << my_sccs.at(i).at(j).getId();
            else 
            cout << "R" << my_sccs.at(i).at(j).getId() << ",";
        }
        cout << endl;
    }
}

void graph::output_pos() {
   map<int, node>::iterator it = node_graph.begin();
   cout << "Post Orders:\n";
   while (it != node_graph.end()) {
       cout << "R" << it->first << ": " << it->second.getPostOrder() << endl;
       it++;
   }
}


void graph::clear_visits() {
    map<int, node>::iterator it = node_graph.begin();
    while (it != node_graph.end()) {
       it->second.markNotVisited();
       it++;
   }
}