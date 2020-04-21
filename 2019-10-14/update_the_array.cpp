// STRATEGY
// We solve with the same trick of littlegirl.cpp:
// for each update operation <l,r,v> on array A we execute A[l] += v and
// A[r+1] += v.
// Instead of doing this on a "dumb" array and then making a final scan to
// manually compute the prefix sum of A, we immediately instantiate A as a BIT.
//
// COST
// In time: for U updates over N elements and then Q queries, O((U+Q)*log(N)).
// In space: O(N) for the BIT.
// (of note: the "dumb" array solution yields O(N + U + Q) time, O(N) space)


#include <vector>
#include <cassert>
#include <iostream>

template <class T>
class fenwick
{
  private:
  std::vector<T> m_a;
  
  static inline size_t parent(const size_t i)
  {
    return i - (i & -i);
  }
  
  static inline size_t get_next(const size_t i)
  {
    return i + (i & -i);
  }
  
  public:
  fenwick(const size_t n)
    : m_a(n + 2)
  {
    assert(n > 0);
  }
  
  void add(const typename std::vector<T>::size_type i, const T k)
  {
    typename std::vector<T>::size_type cur = i + 1;
    do {
      m_a[cur] += k;
    } while ((cur = get_next(cur)) < m_a.size());
  }
  
  T prefix_sum(const typename std::vector<T>::size_type i) const
  {
    typename std::vector<T>::size_type cur = i + 1;
    T sum = 0;
    do {
      sum += m_a[cur];
    } while ((cur = parent(cur)) != 0);
    return sum;
  }
};


int main(int argc, char *argv[])
{
    size_t t, n, u, q;
    

    std::cin >> t;
    for (size_t test = 0; test < t; test++) {
        std::cin >> n >> u;
        fenwick<int32_t> bit(n + 1);
        for (size_t update = 0; update < u; update++) {
            size_t l, r, val;
            std::cin >> l >> r >> val;
            bit.add(l, val);
            bit.add(r + 1, -val);
        }

        std::cin >> q;
        for (size_t query = 0; query < q; query++) {
            size_t index;
            std::cin >> index;
            std::cout << bit.prefix_sum(index) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}

