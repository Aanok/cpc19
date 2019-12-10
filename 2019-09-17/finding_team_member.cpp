// STRATEGY
// We build triples of form (a_ij, i, j), sort them by highest a_ij then start
// going through them assigning pairings in order on a first-come-first-serve
// basis.
//
// COST
// The pairings number in O(N^2) and need to be stored. We also need an O(N)
// array to keep track of assigned pairings, so the total memory cost is O(N^2).
//
// The triples are generated online during input scan for O(N^2) time cost.
// They are sorted for a O(N^2*log(N)) time cost.
// They are popped from the sorted store in O(N^2) time cost.
// The output print costs O(N) operations.
// Thus the overall time cost is O(N^2*log(N)).


#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>


// the contestants will be 0-indexed here
typedef std::tuple<unsigned int, unsigned short, unsigned short> pairing;


int main(int argc, char *arg[])
{
    unsigned short n;
    unsigned int tmp;
    std::vector<pairing> pairings;
    // the contestants will be 1-indexed here so 0 can work as nil
    std::vector<unsigned short> final_pairs;

    std::cin >> n;
    pairings.reserve(n*(n+1)/2);
    final_pairs = std::vector<unsigned short>(2*n, 0);
    for (unsigned short i = 0; i < 2*n; i++) {
        for (unsigned short j = 0; j < i; j++) {
            std::cin >> tmp;
            pairing pair_ij = std::make_tuple(tmp, i, j);
            pairings.push_back(pair_ij);
        }
    }

    std::sort(pairings.begin(),
            pairings.end(),
            [](const pairing &x, const pairing &y) {
                return std::get<0>(x) > std::get<0>(y);
                });

    for (std::vector<pairing>::const_iterator cit = pairings.cbegin();
            cit != pairings.cend(); cit++) {
        unsigned short i = std::get<1>(*cit);
        unsigned short j = std::get<2>(*cit);
        if (final_pairs[i] == 0 && final_pairs[j] == 0) {
            // remember we 1-index here
            final_pairs[i] = j + 1;
            final_pairs[j] = i + 1;
        } else {
        }
    }

    for (std::vector<unsigned short>::const_iterator cit = final_pairs.cbegin();
            cit != final_pairs.cend();
            cit++) {
        std::cout << *cit << " ";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
