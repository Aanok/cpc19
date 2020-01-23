// STRATEGY
// There are two parts to this problem.
//
// The first is to determine if a given number is prime or not. As by
// http://research.cs.wisc.edu/techreports/1990/TR909.pdf we see the classic
// Sieve of Erathosthenes is actually a solid choice of algorithm for small
// inputs, like the ones from the problem. As the problem then requires
// answering many such queries within a given range per instance, we add the
// optimization of precomputing all primes within the range once before starting
// answering queries (we actually keep such a cache persistent between the
// various instances too: no reason to throw away work that may be useful again
// in the future).
//
// The second part regards computing the depth of a node within a tree
// represented by an array of parent node ID's. This is done easily and
// efficiently once you make sure to save the depths of all ancestors of a 
// queried node and not just that of the queried node. A recursive form of the
// algorithm would look something like this:
//
// COMPUTE_DEPTH(parents, node)
//  if (parents[node] == null) then
//      node.depth = 0
//  else
//      if (parents[node].depth == null) then
//          COMPUTE_DEPTH(parents, parents[node])
//      end
//      node.depth = parents[node].depth + 1
//  end
// end
//
// As the trees can hold up to 10^5 nodes, we apply the optimization of
// unrolling the recursive structure into an iterative form by keeping an
// explicit backtracking stack. This is quicker and, most importantly, avoids
// call stack overflows.
//
// COST
// Let N be the size of the company (number of employees).
// The first part takes O(N) time and O(N) space, as we employ a simple
// implementation of the Sieve of Erathostenes using a bitvector.
// The second part likewise takes O(N) time (each node is pushed and popped on
// the stack once) and O(N) space (we save the nodes' depth in an array).


#include <vector>
#include <cmath>
#include <stack>
#include <iostream>


////////// CACHING SIEVE //////////
class caching_sieve
{
    public:
        caching_sieve(const size_t n = 100);
        bool is_prime(const size_t n);
        void update_sieve(const size_t n);

    private:
        size_t m_size;
        std::vector<bool> m_primes;

};


caching_sieve::caching_sieve(const size_t n)
    : m_size(0), m_primes()
{
    update_sieve(n);
}


void caching_sieve::update_sieve(const size_t n)
{
    // a smarter implementation would not throw away the old vector and extend
    // it using a segmented sieve algorithm but this is not necessary for the
    // exercise
    m_primes = std::vector<bool> (n + 1, true);
    size_t p = 2;
    m_primes[0] = false;
    m_primes[1] = false;

    while (p <= std::sqrt(n)) {
        size_t f = p;
        while (p * f <= n) {
            m_primes[p * f] = false;
            f++;
        }
        while (m_primes[++p] == false) ;
    }

    m_size = n;
}


bool caching_sieve::is_prime(const size_t n)
{
    if (n > m_size) {
        update_sieve(n);
    }

    return m_primes[n];
}
///////////////////////////////////


// NB return by value is efficient as by reference due to copy elision
// see http://web.archive.org/web/20140113221447/http://cpp-next.com/archive/2009/08/want-speed-pass-by-value/
std::vector<size_t> 
count_seniors(const std::vector<size_t> &company)
{
    std::vector<size_t> seniors(company.size(), -1); // NB max size_t is a valid sentinel by input constraint
    std::stack<size_t> backtrack;

    for (size_t i = 0; i < company.size(); i++) {
        if (seniors[i] != -1) continue;
        backtrack.push(i);
        while (! backtrack.empty()) {
            size_t j = backtrack.top();
            if (company[j] == 0) {
                seniors[j] = 0;
                backtrack.pop();
            } else if (seniors[company[j] - 1] != -1) {
                seniors[j] = seniors[company[j] - 1] + 1;
                backtrack.pop();
            } else {
                backtrack.push(company[j] - 1);
            }
        }
    }

    return seniors;
}


size_t count_fireable(const std::vector<size_t> &company, caching_sieve &primes)
{
    size_t count = 0;
    std::vector<size_t> seniors = count_seniors(company);

    primes.update_sieve(2 * (company.size() + 1));
    for (size_t i = 0; i < company.size(); i++) {
        if (seniors[i] == 0) continue;
        if (primes.is_prime(i + 1 + seniors[i])) count++;
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
