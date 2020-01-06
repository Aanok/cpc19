// STRATEGY
// Consider a merge step in the Merge Sort algorithm, sorting in ascending
// order.
// Specifically, consider merging LOW[0..l-1] and HIGH[0..h-1] where, of course,
// LOW and HIGH are already sorted internally.
// Assume you are confronting LOW[i] with HIGH[j].
// If LOW[i] > HIGH[j], then HIGH[j] < LOW[i] < LOW[i+1] ... < LOW[l-1]
// (NB strictly less than because all elements are distinct!)
// Which means you have l - i inversions.
// If LOW[i] < HIGH[j], we find no inversions.
//
// COST
// Counting the inversions adds O(N) operations to each merge step of a Merge
// Sort procedure. Thus, the cost is the same as a regular Merge Sort:
// O(N*log(N)).
// No additional memory overhead is required either outside of O(1) for
// bookkeeping.


#include <iostream>
#include <vector>


typedef uint64_t num_type;
typedef unsigned int index_type;


num_type inversion_merge(std::vector<num_type> &array,
        const index_type left,
        const index_type pivot,
        const index_type right)
{
    std::vector<num_type> support;
    num_type count = 0;
    index_type i = left;
    index_type j = pivot + 1;

    support.reserve(right - left + 1);

    // do work while both indices still make sense
    while (i <= pivot && j <= right) {
        if (array[i] <= array[j]) {
            support.push_back(array[i++]);
        } else {
            support.push_back(array[j++]);
            count += pivot - i + 1;
        }
    }

    // clear tails; there will be no more inversions
    while (i <= pivot) {
        support.push_back(array[i++]);
    }
    while (j <= right) {
        support.push_back(array[j++]);
    }

    // write sorted order via side-effect
    std::copy(support.begin(), support.end(), array.begin() + left);
    return count;
}


num_type inversion_count(std::vector<num_type> &array,
        const index_type left,
        const index_type right)
{
    num_type count = 0;

    if (left < right) {
        index_type pivot = (right + left) / 2;
        count += inversion_count(array, left, pivot);
        count += inversion_count(array, pivot + 1, right);
        count += inversion_merge(array, left, pivot, right);
    }

    return count;
}


int main(int argc, char *argv[])
{
    size_t t;
    index_type n;
    std::vector<num_type> array;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        std::cin >> n;
        if (n == 0) continue;
        array.clear();
        array.reserve(n);
        for (index_type j = 0; j < n; j++) {
            num_type tmp;
            std::cin >> tmp;
            array.push_back(tmp);
        }
        std::cout << inversion_count(array, 0, n - 1) << std::endl;
    }    

    return EXIT_SUCCESS;
}
