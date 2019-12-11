#include "graph.h"
graph::graph(vector<Rule> rules) {
    my_rules = rules;
    post_order = 1;
    assign_nodes();
    create_dependencies();
    print_dependencies();
    dfs_rev();
    dfs();
    // debug();
}
graph::~graph(){}

void graph::debug() {
    print_revDependencies();
    cout << endl;
    output_sccs();
    cout << endl;
    output_pos();
}

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

//how do I want to accomplish the dfs()?
//well I need to somehow while loop through the nodes from highest po to lowest
//creating the sccs as I go
//a good way to do that would be a map which would self-order


void graph::dfs() {
    map<int, node>::reverse_iterator it = po_nodes.rbegin();
    vector<node> scc;
    while (it != po_nodes.rend()) {
       node* tmp = &it->second;
       if (tmp->isVisited()) {} //do nothing
       else {
           descend(tmp, scc);
           organizeScc(scc);
           eval_sccs.insert(pair<int,vector<node>>(tmp->getPostOrder(),scc));
           scc.clear();
       }
       it++;
   }
   clear_visits(); //clear the visited var of the nodes
}

void graph::descend(node* tmp, vector<node> &scc) {
    set<int> my_nodes;
    tmp->markVisited();
    my_nodes = tmp->getFriendNodes();
    for (int id : my_nodes) {
        node tmp2 = node_graph.find(id)->second;
        node* tmp3 = &po_nodes.find(tmp2.getPostOrder())->second;
        if (tmp3->isVisited()) {} //do nothing
        else descend(tmp3, scc);
    }
    scc.push_back(*tmp);
    return;
}

void graph::dfs_rev() {
   map<int, node>::iterator it = node_graph.begin();
   while (it != node_graph.end()) {
       node* tmp = &it->second;
       if (tmp->isVisited()) {} //do nothing
       else {
           descend_rev(tmp);
       }
       it++;
   }
    clear_visits(); //clear the visited var of the nodes
    clear_visits2();
}

void graph::descend_rev(node* tmp) {
    // cout << "descend:" << post_order << endl;
    set<int> my_nodes;
    tmp->markVisited();
    my_nodes = tmp->getFriendNodes_rev();
    for (int id : my_nodes) {
        node* tmp2 = &node_graph.find(id)->second;
        if (tmp2->isVisited()) {} //do nothing
        else descend_rev(tmp2);
    }
    tmp->setPostOrder(post_order);
    po_nodes.insert(pair<int,node>(post_order,*tmp));
    post_order++;
    return;
}

void graph::organizeScc(vector<node> &my_scc) {
    for (unsigned i = 0; i < my_scc.size()-1; i++) {
        for (unsigned j = 1; j < my_scc.size(); j++) {
            if (my_scc.at(i).getId() > my_scc.at(j).getId()) { 
                iter_swap(my_scc.begin() + i, my_scc.begin() + (j));
            }
        }
    }
}


void graph::output_sccs() {
    cout<< "SCCs\n";
    map<int, vector<node>>::iterator it = eval_sccs.begin();
    int i = 0;
    while(it != eval_sccs.end()) {
        cout << "SCC:" << i << " ";
        for (unsigned j = 0; j < it->second.size(); j++) {
            cout << "R" << it->second.at(j).getId() << " "; 
        }
        cout << endl;
        it++;
        i++;
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

void graph::clear_visits2() {
    map<int, node>::iterator it = po_nodes.begin();
    while (it != po_nodes.end()) {
       it->second.markNotVisited();
       it++;
   }
}

map<int,vector<node>> graph::getEvalSccs() {
    return eval_sccs;
}