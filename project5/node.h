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
    int post_order;
public:
    node(Rule rule, int id);
    ~node();
    void insert_dependency(int id);
    void insert_rev_dep(int id);
    string depend_toString();
    string revDepend_toString();
    bool isVisited();
    void markVisited();
    void markNotVisited();
    set<int> getFriendNodes();
    set<int> getFriendNodes_rev();
    void setPostOrder(int po);
    int getId();
    int getPostOrder();
    Rule getRule();
};

