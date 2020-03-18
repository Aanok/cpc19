#include <iostream>
#include <vector>
#include <algorithm>


int main (int argc, char *argv[])
{
    uint16_t n, k;
    std::vector<int32_t> input;

    std::cin >> n >> k;
    input.reserve(n);
    k--; // make it 0-indexed

    for (uint16_t i = 0; i < n; i++) {
        int32_t tmp;
        std::cin >> tmp;
        input.push_back(tmp);
    }

    std::sort(input.begin(), input.end());

    std::cout << input[k / n] << " " << input[k % n] << std::endl;

    return EXIT_SUCCESS;
}
