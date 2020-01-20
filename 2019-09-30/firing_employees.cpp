#include <unordered_set>
#include <vector>
#include <cmath>
#include <iostream>


////////// CACHING SIEVE //////////
class caching_sieve
{
    public:
        caching_sieve();
        bool is_prime(const size_t n);

    private:
        size_t m_size;
        std::unordered_set<size_t> m_primes;

        void update_sieve(const size_t n);
};


caching_sieve::caching_sieve()
    : m_size(0), m_primes()
{
    update_sieve(100);
}


void caching_sieve::update_sieve(const size_t n)
{
    std::vector<bool> candidates(n + 1, true);
    size_t p = 2;
    candidates[0] = false;
    candidates[1] = false;

    while (p <= std::sqrt(n)) {
        size_t f = p;
        while (p * f <= n) {
            candidates[p * f] = false;
            f++;
        }
        p++;
        while (candidates[p] == false) p++;
    }

    for (size_t i = 0; i < n; i++) {
        if (candidates[i] == true) {
            m_primes.insert(i);
        }
    }

    m_size = n;
}


bool caching_sieve::is_prime(const size_t n)
{
    if (n > m_size) {
        update_sieve(n);
    }

    return m_primes.find(n) != m_primes.end();
}
///////////////////////////////////


size_t count_seniors(const std::vector<size_t> &company, size_t i)
{
    size_t count = 0;

    while (company[i] != 0) {
        count++;
        i = company[i] - 1;
    }

    return count;
}


size_t count_fireable(const std::vector<size_t> &company, caching_sieve &primes)
{
    size_t count = 0;

    for (size_t i = 0; i < company.size(); i++) {
        size_t seniors = count_seniors(company, i);
        if (seniors == 0) continue;
        if (primes.is_prime(i + 1 + seniors)) count++;
    }

    return count;
}


int main(int argc, char *argv[])
{
    size_t t;
    std::vector<size_t> company;
    caching_sieve primes;

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
        std::cout << count_fireable(company, primes) << std::endl;
    }

    return EXIT_SUCCESS;
}
