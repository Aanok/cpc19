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
