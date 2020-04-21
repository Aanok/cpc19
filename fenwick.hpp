#include <vector>
#include <cassert>

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


    void add_range(const typename std::vector<T>::size_type left,
                    const typename std::vector<T>::size_type right,
                    const T k)
    {
        this->add(left, k);
        this->add(right + 1, -k);
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


    T operator[](const typename std::vector<T>::size_type i) const
    {
        T to_clear = i > 0 ? this->prefix_sum(i - 1) : 0;
        return this->prefix_sum(i) - to_clear;
    }
};
