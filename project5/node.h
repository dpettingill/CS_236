#include <set>
#include "Rule.h"

using namespace std;

class node
{
private:
    /* data */
    set<int> friend_nodes;
    set<int> rev_friend_nodes;
    bool visited;
    int node_id;
    Rule my_rule;
public:
    node(Rule rule, int id);
    ~node();
    void insert_dependency(int id);
    void insert_rev_dep(int id);
    string depend_toString();
    string revDepend_toString();
    bool isVisited();
    void descend(int i);
};
