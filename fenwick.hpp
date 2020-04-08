#include <vector>
#include <cassert>

template <class T>
class fenwick
{
  private:
  std::vector<T> m_a;
  
  inline size_t parent(const size_t i) const
  {
    return i - (i & -i);
  }
  
  inline size_t get_next(const size_t i) const
  {
    return i + (i & -i);
  }
  
  public:
  fenwick(const size_t n)
    : m_a(n + 1)
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
  
  int prefix_sum(const typename std::vector<T>::size_type i) const
  {
    typename std::vector<T>::size_type cur = i + 1;
    T sum = 0;
    do {
      sum += m_a[cur];
    } while ((cur = parent(cur)) != 0);
    return sum;
  }
};
