// STRATEGY
// We scan the traversal array and keep track on a stack of valid nodes we can
// append children to, whether they are the current one or older we can reach
// by backtracking.
//
// As long as the scan finds a smaller element than current (corresponding to a
// left child) we simply push the element on the stack.
//
// When we find a bigger element than current, we pop from the stack all
// nodes that can no longer have children: that means all elements smaller than
// the current.
// (Note: this, together with the above, means the stack is always sorted in
// decreasing order from the bottom)
//
// We keep track of the greatest such "barren" node we have found. Once a new
// element is found in the input that is smaller than this treshold, we know
// the input cannot represent a previsit, as the new element would need to be
// a child of nodes we have determined cannot have any anymore.
//
//
// COST
// Each element from the input gets read, pushed on the stacked and popped
// exactly once, thus the computational and memory cost are O(N).


#include <iostream>
#include <vector>
#include <stack>


size_t is_preorder_bst(std::vector<size_t> const &traversal)
{
    size_t lower_bound = 0; // input is strictly positive
    std::stack<size_t> backtrack;

    for (std::vector<size_t>::const_iterator cit = traversal.cbegin();
            cit != traversal.cend();
            cit++)
    {
        if (*cit < lower_bound) return 0;

        while (! backtrack.empty() && backtrack.top() < *cit) {
            lower_bound = backtrack.top();
            backtrack.pop();
        }

        backtrack.push(*cit);
    }

    return 1;
}


int main(int argc, char *argv[])
{
    size_t t;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        std::vector<size_t> traversal;
        size_t n;

        std::cin >> n;
        traversal.reserve(n);
        for (size_t j = 0; j < n; j++) {
            size_t tmp;
            std::cin >> tmp;
            traversal.push_back(tmp);
        }

        std::cout << is_preorder_bst(traversal) << std::endl;
    }

    return EXIT_SUCCESS;
}
