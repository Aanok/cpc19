// STRATEGY
// Do a first pass to find the smallest even number; if there is one, move it
// to the least significant (rightmost) digit.
// Then, sort the rest of the number.
//
// COST
// Using Counting Sort, given digits (even their ASCII codes) offer a finite
// alphabet, both time and memory cost go by O(N).


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


template <class Iter>
void counting_sort(Iter begin, Iter end, bool reverse = false)
{
    // make counting array only as long as necessary: max + 1 - min + 1
    std::pair<Iter, Iter> minmax = std::minmax_element(begin, end);
    std::vector<size_t>::size_type min = *std::get<0>(minmax);
    std::vector<size_t>::size_type max = *std::get<1>(minmax) + 1;
    std::vector<size_t> counts(max - min + 1, 0);
    std::vector<typename std::iterator_traits<Iter>::value_type>
        sorted(std::distance(begin, end));
    auto sorted_it = sorted.begin();

    // count occurencies
    for (Iter it = begin; it != end; it++) {
        counts[*it - min]++;
    }

    // compound occurrencies
    if (reverse == false) {
        for (std::vector<size_t>::iterator it = counts.begin() + 1;
                it != counts.end();
                it++) {
            *it += *(it - 1);
        }
    } else {
        for (std::vector<size_t>::iterator it = counts.end() - 2;
                it >= counts.begin();
                it--) {
            *it += *(it + 1);
        }
    }

    // compute sort
    for (Iter it = end - 1; it >= begin; --it) {
        // NB the condition breaks if begin == 0 and we underflow
        // but if your architecture has 0 as a valid address that's on you mate
        sorted[counts[*it - min] - 1] = *it;
        counts[*it - min]--;
    }

    // overwrite input with sort
    for (Iter it = begin; it != end; it++) {
        *it = *sorted_it++;
    }
}


void make_largest_even(std::string &num)
{
    unsigned char smallest_even = '8';
    // pretty sure we're not getting 2^64 -2 digits
    // so -1 is a safe invalid value
    size_t smallest_even_index = -1; 

    // find biggest even digit
    for (size_t i = 0; i < num.length(); i++) {
        // NB '0' in ASCII is 48 so evenness is preserved
        if (num[i] % 2 == 0 && num[i] <= smallest_even) {
            smallest_even = num[i];
            smallest_even_index = i;
        }
    }

    // if it exists, move it to the least significant place (rightmost)...
    if (smallest_even_index != -1) {
        unsigned char tmp = num[num.length() - 1];
        num[num.length() - 1] = smallest_even;
        num[smallest_even_index] = tmp;
        // ... and sort the other digits in descending order
        counting_sort(num.begin(), num.end() - 1, true);
    } else {
        // ... otherwise just sort everything
        counting_sort(num.begin(), num.end(), true);
    }
}


int main (int argc, char *argv[]) {
    size_t t;
    std::string num;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        std::cin >> num;
        make_largest_even(num);
        std::cout << num << std::endl;
    }

    return EXIT_SUCCESS;
}
