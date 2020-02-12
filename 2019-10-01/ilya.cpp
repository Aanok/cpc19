// STRATEGY
// After reading the input string S of length N, we simply precompute offline
// an index COUNT such that COUNT[i] = #{ j <= i | S[j] = S[j + 1]}.
// Then, the answer to a query <l,r> is simply COUNT[r-1] - COUNT[l-1].
//
// COST
// We require O(N) memory to store COUNT and O(N) operations to compute it.

#include <iostream>
#include <string>
#include <vector>


int main(int argc, char* argv[])
{
    std::string input;
    std::vector<size_t> counts;
    size_t nqueries;

    // read input string
    std::cin >> input;
    counts.reserve(input.length());
    counts[0] = 0;
    for (size_t i = 1; i < input.length(); i++) {
        counts[i] = counts[i-1] + (input[i] == input[i-1]);
    }

    // read queries
    std::cin >> nqueries;
    for (size_t i = 0; i < nqueries; i++) {
        size_t l, r;
        std::cin >> l >> r;
        std::cout << counts[r-1] - counts[l-1] << std::endl;
    }

    return EXIT_SUCCESS;
}
