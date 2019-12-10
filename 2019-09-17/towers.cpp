// STRATEGY
// The problem consists of finding how many unique elements exist in the input
// sequence and how many there are of the most frequent one.
//
// Since both the input domain and size of input sequence are known beforehand,
// we can solve this by simply allocating an array of counters as long as the
// cardinality of the input domain. The counters start from zero, and we
// increase counter I whenever we witness the number I in the input sequence.
//
// Two bookkeeping variables let us track the number of unique sightings and
// the number of sightings of the most frequent input number.
//
// COST
// For K cardinality of the input domain, we require O(K) memory overhead for
// the array of counters and O(1) for bookkepping variables.
// The time complexity is O(N) as we just need to scan the input sequence.


#include <vector>
#include <iostream>
#include <cassert>


int main(int argc, char *argv[])
{
    unsigned short n, tmp;
    unsigned short max_height = 0;
    unsigned short uniques = 0;
    std::vector<unsigned short> towers(1001, 0);

    std::cin >> n;
    for (unsigned short i = 0; i < n; i++) {
        std::cin >> tmp;
        assert(tmp <= 1000);
        if (towers[tmp] == 0) {
            uniques++;
        }
        towers[tmp]++;
        max_height = std::max(max_height, towers[tmp]);
    }
    std::cout << max_height << " " << uniques << std::endl;

    return EXIT_SUCCESS;
}
