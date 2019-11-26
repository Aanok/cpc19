// STRATEGY:
// We can start computing a MAX_SUM candidate by just adding elements starting
// from the head of the input array. We can think of this (prefix) sum as an
// offset for the start of a new candidate: if the offset is positive, then we
// may add a new element to the current candidate (it would make no sense to
// start a new candidate, since it's offset would be 0, for a lower total); if
// the offset is negative, then we ought to start a new candidate (its new 0
// offset would be better than our current).
// (if the offset is exactly 0, we may choose arbitrarily)
// Of note: PROPERTY2 guarantees that candidates "overlapping" two or more of
// those we consider are no good.
// Then it is just a matter of keeping the best candidate we found.
//
// COST:
// Computing the various candidates only requires a scan of the input array and
// a fixed number of bookkeeping variables, for an O(N) computational and O(1)
// memory cost.

#include <iostream>
#include <vector>
#include <climits>


int kadane(std::vector<int> const& input)
{
    int sum = 0;
    int best = INT_MIN;

    for (auto cit = input.cbegin(); cit != input.cend(); cit++) {
       if (sum < 0) {
           sum = *cit;
       } else {
           sum += *cit;
       }

       if (sum > best) {
           best = sum;
       }
    }

    return best;
}


int main(int argc, char *argv[])
{
    size_t t, n;
    std::vector<int> results;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        std::vector<int> input;
        std::cin >> n;
        for (size_t j = 0; j < n; j++) {
            int tmp;
            std::cin >> tmp;
            input.push_back(tmp);
        }
        results.push_back(kadane(input));
    }

    for (auto cit = results.cbegin(); cit != results.cend(); cit++) {
        std::cout << *cit << std::endl;
    }

    return 0;
}
