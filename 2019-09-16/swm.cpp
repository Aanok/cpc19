#include <iostream>
#include <vector>
#include <deque>


void maximum_sliding_window(std::vector<size_t> const &input, size_t k)
{
    static std::deque<size_t> deque;
    deque.clear();

    for (size_t i = 0; i < input.size(); i++) {
        while (! deque.empty() && i >= k && deque.front() <= i - k) {
            deque.pop_front();
        }
        while (! deque.empty() && input[deque.back()] <= input[i]) {
            deque.pop_back();
        }
        deque.push_back(i);
        if (i >= k - 1) {
            std::cout << input[deque.front()] << " ";
        }
    }
}


int main(int argc, char *argv[])
{
    size_t t, n, k;

    std::cin >> t;

    for (size_t i = 0; i < t; i++) {
        std::vector<size_t> input;
        std::cin >> n >> k;
        input.reserve(n);
        for (size_t j = 0; j < n; j++) {
            size_t tmp;
            std::cin >> tmp;
            input.push_back(tmp);
        }
        maximum_sliding_window(input, k);
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
