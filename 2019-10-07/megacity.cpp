// STRATEGY
// Sort the locations by distance from Tomsk, then greedily add their population
// till you reach the required treshold.
//
// COST
// O(N) memory to store the input.
// O(N*log(N)) computation due to the sort operation.


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>


struct suburb {
    double dist;
    uint32_t pop;

    friend bool operator<(const struct suburb& x, const struct suburb& y)
    {
        return x.dist < y.dist;
    }
};


int main(int argc, char *argv[])
{
    uint16_t n;
    uint32_t s;
    std::vector<struct suburb> landscape;

    std::cin >> n >> s;

    landscape.reserve(n);

    for (uint16_t i = 0; i < n; i++) {
        int16_t x, y;
        uint32_t pop;
        std::cin >> x >> y >> pop;
        landscape.push_back({std::hypot(x, y), pop});
    }

    std::sort(landscape.begin(), landscape.end());

    auto bound = std::find_if(landscape.cbegin(),
            landscape.cend(),
            [&s](const struct suburb& x) {
                s += x.pop;
                return s >= 1000000;
                });

    std::cout << std::setprecision(8);
    if (bound == landscape.cend()) {
        std::cout << -1;
    } else {
        std::cout << bound->dist;
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
