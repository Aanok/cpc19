// STRATEGY:
// It can be shown that SUM(1, 2 ... N) = N * (N + 1) / 2.
// It is thus enough to sum the elements of each input array and compare them
// with the above formula to find which element is missing.
//
// COST:
// The formula has O(1) computational and memory cost.
// Scanning the array to compute the sum has O(N) computational and O(1) memory
// cost.
// Thus the overall cost per input array is O(N).

#include <iostream>
#include <vector>


int missing(std::vector<size_t> const &input)
{
    size_t sum = 0;

    for (auto cit = input.cbegin(); cit != input.cend(); cit++) {
        sum += *cit;
    }

    // N.B. input is one element short of N
    return (input.size() + 1) * (input.size() + 2) / 2 - sum;
}


int main(int argc, char *argv[])
{
    size_t t, n;
    std::vector<size_t> results;

    std::cin >> t;
    results.reserve(t);
    for (size_t i = 0; i < t; i++) {
        std::vector<size_t> input;
        std::cin >> n;
        input.reserve(n);
        for (size_t j = 0; j < n - 1; j++) {
            size_t tmp;
            std::cin >> tmp;
            input.push_back(tmp);
        }
        results.push_back(missing(input));
    }

    for (auto cit = results.cbegin(); cit != results.cend(); cit++) {
        std::cout << *cit << std::endl;
    }

    return 0;
}
