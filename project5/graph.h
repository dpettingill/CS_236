#include "Database.h"
#include "node.h"
#include "Rule.h"
#include <vector>


class graph
{
private:
    /* data */
    map<int, node> node_graph;
    vector<Rule> my_rules;
public:
    graph(vector<Rule> rules);
    ~graph();
    void assign_nodes();
    void create_dependencies();
    void print_dependencies();
    void print_revDependencies();
    void dfs();
    void dfs_rev();
};

