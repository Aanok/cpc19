// STRATEGY
// Let S be the total sum of the array.
// As the input must be split in three segments of equal sum, if S mod 3 != 0,
// there is no solution.
// Otherwise, we single out those positions which are viable as "i-1" indices 
// (that is, whose prefix sum in the input equals S/3); in particular, we
// compute a prefix sum array of their count.
// Next, we single out those positions which are viable as "j+1" indices (that
// is, whose suffix sum in the input equals S/3): each of those is compatible
// with "i" indices where i <= j, which we can find thanks to the prefix array.
// 
// NB: painful care is to be taken in aligning the indices.
//
// COST
// We need O(N) space to store the input and the i-prefixes.
// We need O(N) time to scan the input a couple times.

#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    uint64_t n, count;
    int64_t sum, one_third;
    std::vector<int64_t> input;
    std::vector<uint64_t> good_i;

    std::cin >> n;
    input.reserve(n); // = std::vector<int64_t>(n, 0);
    good_i.reserve(n); // = std::vector<uint64_t>(n, 0);

    sum = 0;
    for (size_t i = 0; i < n; i++) {
        int64_t tmp;
        std::cin >> tmp;
        input.push_back(tmp);
        sum += tmp;
    }

    if (sum % 3 != 0) {
        std::cout << "0" << std::endl;
        return EXIT_SUCCESS;
    }
    
    one_third = sum / 3;

    sum = input[0];
    good_i.push_back(sum == one_third ? 1 : 0);
    for (auto cit = input.cbegin() + 1; cit != input.cend(); cit++) {
        sum += *cit;
        good_i.push_back(good_i.back());
        if (sum == one_third) good_i.back()++;
    }

    sum = 0;
    count = 0;
    for (size_t k = n - 1; k >= 2;  k--) {
        sum += input[k];
        if (sum == one_third) count += good_i[k - 2];
    }

    std::cout << count << std::endl;

    return EXIT_SUCCESS;
}
