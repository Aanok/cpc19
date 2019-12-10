// STRATEGY
// Nut: consider merging low[0..L-1] and high[0..h-1]
// When it happens that you pick from high,
// high[j] < low[i] < low[i+1] ... < low[L-1]
// (NB strictly less than because all elements are distinct!)
// Then you have L - i inversions.


#include <iostream>
#include <vector>


typedef unsigned int num_type;
typedef unsigned int index_type;


index_type inversion_merge(std::vector<num_type> &array,
        const index_type left,
        const index_type pivot,
        const index_type right)
{
    std::vector<num_type> support;
    index_type count = 0;
    index_type i = left;
    index_type j = pivot + 1;

    support.reserve(right - left + 1);

    // do work while both indices still make sense
    while (i <= pivot && j <= right) {
        if (array[i] < array[j]) {
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


index_type inversion_count(std::vector<num_type> &array,
        const index_type left,
        const index_type right)
{
    index_type count = 0;

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
