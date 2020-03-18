// COST
// Computation: O(N*log(N)
// Space: O(N)


#include <iostream>
#include <vector>
#include <algorithm>


int main (int argc, char *argv[])
{
    uint64_t n, k, multiplicity, i;
    uint64_t smaller = 0;
    std::vector<int32_t> input;

    std::cin >> n >> k;
    input.reserve(n);
    k--; // make it 0-indexed

    for (uint64_t i = 0; i < n; i++) {
        int32_t tmp;
        std::cin >> tmp;
        input.push_back(tmp);
    }

    std::sort(input.begin(), input.end());
    
    i = k / n;

    multiplicity = std::count(input.cbegin(), input.cend(), input[i]);

    while (smaller < n && input[smaller] != input[i]) smaller++;

    std::cout
        << input[k / n]
        << " " << input[(k - smaller * n) / multiplicity]
        << std::endl;

    return EXIT_SUCCESS;
}
