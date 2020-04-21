// STRATEGY
// The solution is as reported on the professor's notes. The only bit that
// requires some care is that, in line of principle, we would want the BIT to
// index all of the possible segment end point values, which is clearly
// infeasible in terms of memory. Thus, a class offering a remapping of unique
// indices to the most compact interval possible is employed.
//
// COST
// We must sort the N segments, then run a constant amount of BIT operations
// over each of them, for a total of O(N*log(N)) operations.
// With a couple arrays and a BIT, we require only O(N) memory.


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>


typedef struct segment {
    int32_t l, r;
    uint32_t id;
} segment;

typedef struct result {
    uint32_t id, val;
} result;


template <class T>
class remapper
{
    private:
    std::vector<std::pair<T,typename std::vector<T>::size_type>> m_a;
    

    inline static bool compare_only_first(const std::pair<T,
            typename std::vector<T>::size_type> &x,
            const std::pair<T,typename std::vector<T>::size_type> &y)
    {
        return x.first < y.first;
    }
    

    public:
    remapper()
    : m_a()
    { }
    

    inline typename std::vector<T>::size_type get_map_of(const T val) const
    {
        typename std::vector<T>::size_type low = 0;
        typename std::vector<T>::size_type high = m_a.size() - 1;
        typename std::vector<T>::size_type mid = low + (high - low) / 2;
        while (low <= high && mid < m_a.size()) {
            if (m_a[mid].first == val) return mid;
            else if (m_a[mid].first < val) low = mid + 1;
            else high = mid - 1;
            mid = low + (high - low) / 2;
        }
        return -1;
    }
    

    inline void remap(bool in_place = true)
    {
        if (in_place) {
            std::sort(m_a.begin(), m_a.end());
        } else {
            std::sort(m_a.begin(), m_a.end(), compare_only_first);
        }
    }
    

    inline void append(const T val)
    {
        m_a.push_back(std::make_pair(val, m_a.size()));
    }
    

    inline typename std::vector<T>::size_type get_original_index_of(const T val) const
    {
        return (std::lower_bound(m_a.cbegin(),
                    m_a.cend(),
                    std::make_pair(val, 0),
                    compare_only_first))->second;
    }
};


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


int main(int argc, char *argv[])
{
    uint32_t n;
    std::cin >> n;

    std::vector<uint32_t> results(n);
    std::vector<segment> segments;
    fenwick<uint32_t> bit(n);
    remapper<int32_t> map;

    // input
    segments.reserve(n);
    for (uint32_t i = 0; i < n; i++) {
        int32_t l, r;
        std::cin >> l >> r;
        segments.push_back({l, r, i});
        map.append(r);
    }

    // sort segments by decreasing l and compute remapping of r end points
    std::sort(segments.begin(),
            segments.end(),
            [](const segment &a, const segment &b){
                return a.l > b.l;
                });
    map.remap();

    // compute
    for (uint32_t i = 0; i < n; i++) {
        uint32_t idx_r = map.get_map_of(segments[i].r);
        bit.add(idx_r, 1);
        results[segments[i].id] = bit.prefix_sum(idx_r) - 1;
    }

    // output
    for (auto cit = results.cbegin(); cit != results.cend(); cit++) {
        std::cout << *cit << std::endl;
    }

    return EXIT_SUCCESS;
}

