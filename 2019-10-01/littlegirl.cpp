// STRATEGY
// The fundamental intuition is that the input elements that appear in the most
// query intervals should be the largest.
//
// Thus:
// - Read input and sort it.
// - Read query intervals; in line of principle we would represent these as an
//   array of lenght N initialized to 0 everywhere, then, for query interval
//   (L,R) we would increase by one the value of all elements between L and R.
//   This however would be too expensive (O(Q*N) for Q queries), so we rather
//   increase by 1 the value at L and decrease by 1 the value at R+1: in this
//   way, we obtain the frequency counts we need by computing the prefix sum of
//   the array after having read all queries.
// - Sort query array (with the same ordering as the input array).
// - Scan the two sorted arrays in parallel, multiplying the i-th largest
//   element by the i-th largest frequency, accumulating the total.
// 
// COST
// Computational: O(N) to read the input, O(N*log(N)) to sort it, O(N) to read
// the queries (would be O(Q+N) for Q queries, but by hypothesis we know Q
// belongs to O(N)), O(N) to compute the prefix sum, O(N*log(N)) to sort the
// queries, O(N) for the final scan.
//   --> O(N*log(N))
//
// Memory: O(N) to store the input and O(N) to store the queries.

#include <iostream>
#include <vector>
#include <algorithm>


int main(int argc, char *argv[])
{
    uint32_t n, q;
    uint64_t sum;
    std::vector<uint32_t> input;
    std::vector<int32_t> queries;

    std::cin >> n >> q;
    input.reserve(n);
    queries = std::vector<int32_t>(n, 0);

    // read input
    for (uint32_t i = 0; i < n; i++) {
        uint32_t tmp;
        std::cin >> tmp;
        input.push_back(tmp);
    }

    // sort input
    std::sort(input.begin(), input.end());

    for (uint32_t i = 0; i < q; i++) {
        uint32_t l, r;
        std::cin >> l >> r;
        queries[l - 1]++;
        if (r != n) {
            queries[r]--;
        }
    }

    // compute prefix sum of queries
    for (auto it = queries.begin() + 1; it < queries.end(); it++) {
        *it += *(it - 1);
    }

    // sort queries
    std::sort(queries.begin(), queries.end());

    // compute sum
    sum = 0;
    for (uint32_t i = 0; i < n; i++) {
        sum += input[i] * static_cast<uint64_t>(queries[i]);
    }

    std::cout << sum << std::endl;

    return EXIT_SUCCESS;
}
