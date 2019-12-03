// STRATEGY:
// The fundamental observation to make is that the water level in the reservoir
// is higher the further in towards the middle, away from the edges.
// This is natural once you consider that, over a given stretch of land, the two
// tallest pilons will form a pool between each other. At that point, there will
// be two other stretches of land to consider recursively for the same argument
// to the left and right of this new pool. But their pilons will be shorter,
// thus the water level lower.
//
// It is thus enough to start scanning the landscape from its rightmost and
// leftmost edges towards the center, considering a water level as high as the
// last seen pilon and filling in the reservoir accordingly.
//
//
// COST:
// There is an O(1) memory overhead for bookkeeping variables.
// There is an O(N) computational cost for a linear scan of the input array.
//
//
// BONUS WORSE SOLUTION
// Another approach is to sort all pilons into a Binary Search Tree, tallest
// first and left and right children of each node pointing to the tallest pilon
// respectively to the geometric left and right of their parent.
// You start from the tallest pilon and fill a pool to its left child (the
// tallest pilon on its left). Then you do the same from the child to its own
// left-child and so on recursively till the end of the landscape. Likewise to
// the right side, mutatis mutandis.
// The solution has cost O(N*log(N)) due to building the BST.

#include <iostream>
#include <vector>

size_t get_rain(std::vector<size_t> const &terrain)
{
    static size_t water;
    auto left = terrain.cbegin();
    auto right = terrain.cend() - 1;
    size_t water_line = 0;

    water = 0;
    while (left != right) {
        if (*left <= *right) {
           water_line = std::max(*left, water_line);
           water += water_line - *left;
           left++;
        } else {
           water_line = std::max(*right, water_line);
           water += water_line - *right;
           right--;
        }
    }

    return water;
}


int main(int argc, char *argv[])
{
    size_t t, n;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        std::vector<size_t> terrain;

        std::cin >> n;
        terrain.reserve(n);
        for (size_t j = 0; j < n; j++) {
            size_t feature;
            std::cin >> feature;
            terrain.push_back(feature);
        }
        std::cout << get_rain(terrain) << std::endl;
    }

    return EXIT_SUCCESS;
}
