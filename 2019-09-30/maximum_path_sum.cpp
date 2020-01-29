// STRATEGY
// We simply do a post-visit of the tree.
// Each node recursively receives, per each subtree, the weight of the path of
// maximum weight from the root of the subtree to any of its leaves. The node
// offers the connection between two maximal paths, creating the maximal path
// from leaf to leaf for the subtree that has it as its root.
//
// COST
// There is memory overhead in O(H), where H is the height of the input tree,
// as we perform a depth-first seach and we need O(1) global bookkeeping
// variables and O(1) bookkeeping variables per node.
// The computational cost is O(N) as usual per a tree visit.


#include <limits>
#include <algorithm>


// translation unit-level statics are a very C thing but it's perfectly
// sensible in this case
static int s_max_path;


int max_path_sum(struct Node *node)
{
    if (node == nullptr) return 0;

    int l_guess = max_path_sum(node->left);
    int r_guess = max_path_sum(node->right);
    
    s_max_path = std::max(s_max_path, l_guess + r_guess + node->data);
    
    return std::max(l_guess, r_guess) + node->data;
}


int maxPathSum(struct Node *root)
{
    // NB the spec doesn't say what to do when root == nullptr
    // so i choose to do nothing, which means returning int_min
    s_max_path = std::numeric_limits<int>::min();
    max_path_sum(root);
    return s_max_path;
}
