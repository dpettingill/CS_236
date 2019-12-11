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
    int post_order;
    map<int, vector<node>> eval_sccs; //the post order (int) and the corresponding scc to evaluate
public:
    graph(vector<Rule> rules);
    ~graph();
    void debug();
    void assign_nodes();
    void create_dependencies();
    void print_dependencies();
    void print_revDependencies();
    void dfs();
    void dfs_rev();
    void descend_rev(node* tmp, vector<node> &scc);
    void descend(node* tmp);
    void output_sccs();
    void output_pos();
    void clear_visits();
    map<int,vector<node>> getEvalSccs();
};

