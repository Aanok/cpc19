/* General strategy:
Consider query intervals. The element that appears in the most query intervals must be the largest. The second most frequent element must be the second largest etc.
*/

#include <iostream>
#include <vector>
#include <algorithm>


// TODO: fix this with prof's suggestion of using prefix sum
template <class RandomIt>
void inc_by_one(RandomIt start, const RandomIt end)
{
    while (start != end) {
        *start = *start + 1;
        start++;
    }
}


int main(int argc, char *argv[])
{
    uint32_t n, q;
    uint64_t sum;
    std::vector<uint32_t> input;
    std::vector<uint32_t> queries;

    std::cin >> n >> q;
    input.reserve(n);
    queries = std::vector<uint32_t>(n, 0);

    for (uint32_t i = 0; i < n; i++) {
        uint32_t tmp;
        std::cin >> tmp;
        input.push_back(tmp);
    }

    std::sort(input.begin(),
            input.end(),
            [](const uint32_t x, const uint32_t y) { return x > y; });

    for (uint32_t i = 0; i < q; i++) {
        uint32_t l, r;
        std::cin >> l >> r;
        inc_by_one(queries.begin() + l - 1, queries.begin() + r);
    }

    std::sort(queries.begin(),
            queries.end(),
            [](const uint32_t x, const uint32_t y) { return x > y; });

    sum = 0;
    for (uint32_t i = 0; i < n; i++) {
        sum += input[i] * queries[i];
    }

    std::cout << sum << std::endl;

    return EXIT_SUCCESS;
}
