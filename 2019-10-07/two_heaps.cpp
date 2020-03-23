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
    std::vector<struct helper> helpers(101, {0,0,0});
    size_t h1_count = 0;
    size_t h1_uniques = 0;
    size_t h2_count = 0;
    size_t h2_uniques = 0;

    std::cin >> n;
    heaped_nums.reserve(n);

    for (size_t i = 0; i < n; i++) {
        uint8_t input;
        std::cin >> input;
        heaped_nums.push_back({input, 0});
        helpers[input].degree++;
    }

    // first pass: split elements with degree > 1
    for (auto it = heaped_nums.begin(); it != heaped_nums.end(); it++) {
        struct helper *it_helper = &helpers[it->num];
        if (it_helper->degree <= 1) continue;
        if (it_helper->in_h1 > it_helper->in_h2) {
            it->assigned_heap = 2;
            it_helper->in_h2++;
            h2_count++;
            if (it_helper->in_h2 == 0) {
                h2_uniques++;
            }
        } else {
            it->assigned_heap = 1;
            it_helper->in_h1++;
            h1_count++;
            if (it_helper->in_h1 == 0) {
                h1_uniques++;
            }
        }
    }

    // second pass: split elements with degree == 1
    for (auto it = heaped_nums.begin(); it != heaped_nums.end(); it++) {
        if (helpers[it->num].degree > 1) continue;
        if (h1_uniques < h2_uniques && h1_count < h2_count) {
            it->assigned_heap = 1;
            h1_count++;
            h1_uniques++;
        } else {
            it->assigned_heap = 2;
            h2_count++;
            h2_uniques++;
        }
    }

    // emit total count
    std::cout << h1_uniques * h2_uniques;

    // emit assignment map
    for (auto cit = heaped_nums.cbegin(); cit != heaped_nums.cend(); cit++) {
        std::cout << cit->assigned_heap << " ";
    }
    std::cout << std::endl;

    exit(EXIT_SUCCESS);
}
            





