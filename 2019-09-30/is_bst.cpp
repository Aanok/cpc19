// STRATEGY
// The BST property requires that ALL nodes in the left subtree have values
// less than the root and ALL nodes in the right subtree have values greater
// than the root. The property must be respected recursively by all subtrees.
//
// We must then make sure that
// max_value(root.left) < root.data
// and
// min_value(root.right) > root.data
//
// COST
// The computational cost for N nodes is O(N) as we visit each node exactly
// once. The memory cost for a height H is O(H) as we call a function
// recursively from root to leaves.


#include <limits>
#include <algorithm>


struct minmax {
    int min;
    int max;
    bool is_bst;
};


struct minmax is_bst_minmax(Node *node)
{
    if (node == nullptr) {
        return {
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min(),
            true
        };
    }

    struct minmax mm_l = is_bst_minmax(node->left);
    struct minmax mm_r = is_bst_minmax(node->right);

    return {
        std::min(std::min(mm_l.min, mm_r.min), node->data),
        std::max(std::max(mm_l.max, mm_r.max), node->data),
        mm_l.is_bst
            && mm_l.max < node->data
            && mm_r.is_bst
            && mm_r.min > node->data
    };
}


bool isBST(Node* root)
{
    if (root == nullptr) return true;

    struct minmax mm_l = is_bst_minmax(root->left);
    struct minmax mm_r = is_bst_minmax(root->right);

    return mm_l.is_bst
        && mm_l.max < root->data
        && mm_r.is_bst
        && mm_r.min > root->data;
}
