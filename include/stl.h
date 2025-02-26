#ifndef STL_H
#define STL_H
#include <numeric>
#include <algorithm>
inline void initial_vector_with_3_multiples(std::vector<int> &v, size_t size) {
    v.resize(size);
    int multiple = 1;

    std::generate(v.begin(), v.end(), [&multiple]() {
        return 3 * multiple++;
    });
}

inline int count_unique_above(std::vector<int> v, int n) {
    std::set<int> unique_elements(v.begin(), v.end());

    int count = std::count_if(unique_elements.begin(), unique_elements.end(), [n](int x) {
        return x > n;
    });

    return count;
}

inline std::string vector_to_string(std::vector<int> v, char separator) {
    std::reverse(v.begin(), v.end());
    return std::accumulate(v.begin(), v.end(), std::string(), [separator](const std::string& acc, int num) {
        return acc.empty() ? std::to_string(num) : acc + separator + std::to_string(num);
    });
}

inline void square_elements(std::vector<int>& v) {
    std::transform(v.begin(), v.end(), v.begin(), [](int x) {
        return x * x;
    });
}

inline void copy_if_even(const std::vector<int>& source, std::vector<int>& destination)
{
    destination.clear();
    std::copy_if(source.begin(), source.end(), std::back_inserter(destination), [](int x) {
        return x % 2 == 0;
    });
}


#endif //STL_H