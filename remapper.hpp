#include <vector>
#include <utility>
#include <algorithm>


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
