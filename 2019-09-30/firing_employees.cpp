#include <iostream>
#include <cmath>
#include <vector>

// TODO: precompute all primes once per company instead of once per employee

bool is_prime(const size_t n)
{
    std::vector<bool> candidates(n + 1, true);
    size_t p = 2;
    candidates[0] = false;
    candidates[1] = false;

    while (true) {
        if (p > std::sqrt(n)) return true;
        size_t f = p;
        while (p * f <= n) {
            if (p * f == n) return false;
            candidates[p * f] = false;
            f++;
        }
        p++;
        while (candidates[p] == false) p++;
    }
}


size_t count_seniors(const std::vector<size_t> &company, size_t i)
{
    size_t count = 0;

    while (company[i] != 0) {
        count++;
        i = company[i] - 1;
    }

    return count;
}


size_t count_fireable(const std::vector<size_t> &company)
{
    size_t count = 0;

    for (size_t i = 0; i < company.size(); i++) {
        size_t seniors = count_seniors(company, i);
        if (seniors == 0) continue;
        if (is_prime(i + 1 + seniors)) count++;
    }

    return count;
}


int main(int argc, char *argv[])
{
    size_t t;
    std::vector<size_t> company;

    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        size_t n;
        std::cin >> n;
        company.clear();
        company.reserve(n);
        for (size_t j = 0; j < n; j++) {
            size_t tmp;
            std::cin >> tmp;
            company.push_back(tmp);
        }
        std::cout << count_fireable(company) << std::endl;
    }

    return EXIT_SUCCESS;
}
