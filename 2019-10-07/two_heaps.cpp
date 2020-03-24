// STRATEGY
// First of all, let U1 and U2 be the number of unique elements present in each
// heap (that is, discarding repetitions). We see that the number of resulting
// combinations is U1*U2, which is maximized when U1 = U2.
//
// Then, observe that the universe from which elements are picked is bounded
// (and very small), which allows us to feasibly maintain a table of metadata
// for each element.
//
// We proceed as follows:
// Read the input and keep track of the degree of multiplicity of each element
// (i.e. how many times it has been submitted).
// Do a first pass over the input where you consider only elements with
// degree > 1: assign exactly one to each of the heaps.
// Do a second pass over the input where you consider only elements with
// degree == 1: assign them in turn to the heap which contains the least unique
// elements.
// Do a final third pass over the input where you consider only unassigned
// elements with degree > 1: assign them arbitrarily to whichever heap still has
// space available.
//
//
// COST
// We save the input and keep a fixed amount of metadata per each element, plus
// some fixed amount of metadata per each element of the universe, plus some
// bookkeeping per each heap: for a universe of size K this means O(N + K)
// memory. However, for the proposed problem specifically K may be considered
// O(N) or even O(1), amounting to a total O(N) memory.
// We do three linear scans over the input: O(N) computations.


#include <iostream>
#include <vector>


struct heaped_num {
    uint8_t num, assigned_heap;
};


struct helper {
    uint8_t degree, in_h1, in_h2;
};


int main(int argc, char *argv[])
{
    size_t n;
    std::vector<struct heaped_num> heaped_nums;
    std::vector<struct helper> helpers(100, {0,0,0});
    size_t h1_count = 0;
    size_t h1_uniques = 0;
    size_t h2_count = 0;
    size_t h2_uniques = 0;

    std::cin >> n;
    heaped_nums.reserve(2*n);

    for (size_t i = 0; i < 2*n; i++) {
        unsigned int input;
        std::cin >> input;
        heaped_nums.push_back({(uint8_t)input, 0});
        helpers[input].degree++;
    }

    // first pass: make sure each heap has exactly one of the elements with
    // degree > 1
    for (auto it = heaped_nums.begin(); it != heaped_nums.end(); it++) {
        struct helper *it_helper = &helpers[it->num];
        if (it_helper->degree <= 1) continue;
        if (it_helper->in_h1 == 0 && h1_count < n) {
            it->assigned_heap = 1;
            h1_count++;
            h1_uniques++;
            it_helper->in_h1 = 1;
        } else if (it_helper->in_h2 == 0 && h2_count < n) {
            it->assigned_heap = 2;
            h2_count++;
            h2_uniques++;
            it_helper->in_h2 = 1;
        }
    }

    // second pass: split elements with degree == 1 to keep uniques count
    // balanced between the two heaps
    for (auto it = heaped_nums.begin(); it != heaped_nums.end(); it++) {
        struct helper *it_helper = &helpers[it->num];
        if (it_helper->degree != 1) continue;
            if (h1_uniques < h2_uniques && h1_count < n) {
                it->assigned_heap = 1;
                h1_count++;
                h1_uniques++;
            } else {
                it->assigned_heap = 2;
                h2_count++;
                h2_uniques++;
            }
    }

    // third pass: arbitrarily assign leftovers with degree > 1
    for (auto it = heaped_nums.begin(); it != heaped_nums.end(); it++) {
        struct helper *it_helper = &helpers[it->num];
        if (it_helper->degree == 1) continue;
        if (it->assigned_heap != 0) continue;
        if (h1_count < n) {
            it->assigned_heap = 1;
            it_helper->in_h1++; // completely unnecessary but w/e
            h1_count++;
        } else {
            it->assigned_heap = 2;
            it_helper->in_h2++;
            h2_count++;
        }
    }

    // emit total count
    std::cout << (unsigned int)(h1_uniques * h2_uniques) << std::endl;

    // emit assignment map
    for (auto cit = heaped_nums.cbegin(); cit != heaped_nums.cend(); cit++) {
        std::cout << (unsigned int)cit->assigned_heap << " ";
    }
    std::cout << std::endl;

    exit(EXIT_SUCCESS);
}
            





