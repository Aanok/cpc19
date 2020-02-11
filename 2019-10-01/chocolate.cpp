// STRATEGY
// We approach the problem like a game theory simulation, letting Alice and Bob
// eat the chocolate one piece at a time, every "turn" letting the player who
// has eaten the least chocolate eat the next piece, breaking ties in favour of
// Alice.
//
// COST
// We need to store the chocolate layout for O(N) memory overhead, plus an O(1)
// amount of bookkeeping variables.
// Computationally, we just have to run a linear scan of the array, for O(N)
// operations.

#include <iostream>
#include <vector>


int main(int argc, char *argv[])
{
    size_t n;
    std::vector<size_t> choc;

    std::cin >> n;
    choc.reserve(n);
    for (size_t i = 0; i < n; i++) {
        size_t tmp;
        std::cin >> tmp;
        choc.push_back(tmp);
    }

    // factoring code that runs only once into a separate function makes it less
    // readable, since you need to follow a redirection to see what it does
    {
        size_t alice_idx = 0;
        size_t alice_choc = 0;
        size_t bob_idx = n - 1;
        size_t bob_choc = 0;
        
        while (alice_idx <= bob_idx) {
            if (alice_choc <= bob_choc) {
                alice_choc += choc[alice_idx++];
            } else {
                bob_choc += choc[bob_idx--];
            }
        }

        std::cout << alice_idx << " " << n - bob_idx - 1 << std::endl;
    }

    return EXIT_SUCCESS;
}
