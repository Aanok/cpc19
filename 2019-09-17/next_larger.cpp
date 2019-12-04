// STRATEGY
// We scan the input array left to right and keep track of elements we have not
// yet found a next_larger for using a LIFO data structure.
// At each iteration we check the new element from the input array against the
// top of such a stack. If the new element is smaller, we push it on top and
// pass on. If it is bigger, we recursively pop the top of the stack, recording
// the new element as the next_larger for the popped one.
// 
// It is evident how this enforces the invariant that, once we have considered
// a new element X from the input array, all elements on the stack will be
// smaller than X. In fact, consider the following argument by induction on the
// input array elements: the new element X will be either smaller than what is
// on top of the stack or the stack will be popped until what is on top is
// smaller than X. By the inductive hypothesis, such an item on top will then
// also be smaller than anything existing below it in the rest of the stack.
// Thus, by transitive property X will be smaller than any element in the stack.
//
// This more crucially means that the stack will be sorted, with smaller
// elements towards the top.
//
// In this way, every time we examine a new element X from the input array, we
// can quickly find all elements to its left that are smaller than X and that
// have not yet found their next_larger (if any exist), which would be X.
//
// COST
// Every element of the input array is pushed on and popped from the stack
// exactly once: the scan operation takes O(N) time and requires O(N) memory.
// The printing operation and identification of those elements that do not have
// a next_larger also have O(N) cost in both time and memory (they require
// allocating and then scanning an array as long as the input).
// The overall cost is thus linear.


#include <iostream>
#include <vector>
#include <stack>


void next_larger_element(std::vector<size_t> const &input)
{
    static std::stack<size_t> stack;
    std::vector<size_t> next(input.size(), -1); // N < 10^7 so good OOB

    // scan array
    for (size_t i = 0; i < input.size(); i++) {
    while (! stack.empty() && input[stack.top()] < input[i]) {
            next[stack.top()] = i;
            stack.pop();
        }
        stack.push(i);
    }
    // clear of elements without a next larger
    while (! stack.empty()) {
        stack.pop();
    }

    // print
    for (std::vector<size_t>::const_iterator cit = next.cbegin();
            cit != next.end();
            cit++) {
        if (*cit == -1) {
            std::cout << -1;
        } else {
            std::cout << input[*cit];
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}


int main(int argc, char *argv[])
{
    size_t t, n;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        std::vector<size_t> input;
        std::cin >> n;
        input.reserve(n);
        for (size_t j = 0; j < n; j++) {
            size_t tmp;
            std::cin >> tmp;
            input.push_back(tmp);
        }
        next_larger_element(input);
    }

    return EXIT_SUCCESS;
}
