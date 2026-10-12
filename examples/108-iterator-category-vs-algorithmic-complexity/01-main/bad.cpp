// std: c++17
// std::lower_bound compiles for std::list but needs O(n) iterator steps: only the comparisons are O(log n).
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <list>
#include <numeric>

struct CountingIt {                                // a list iterator that counts its increments
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = const int*;
    using reference = const int&;
    std::list<int>::const_iterator it;
    long* steps;
    reference operator*() const { return *it; }
    CountingIt& operator++() { ++*steps; ++it; return *this; }
    CountingIt operator++(int) { auto t = *this; ++*this; return t; }
    CountingIt& operator--() { ++*steps; --it; return *this; }
    CountingIt operator--(int) { auto t = *this; --*this; return t; }
    bool operator==(const CountingIt& o) const { return it == o.it; }
    bool operator!=(const CountingIt& o) const { return it != o.it; }
};

int main() {
    std::list<int> l(1 << 16);
    std::iota(l.begin(), l.end(), 0);
    long steps = 0, compares = 0;
    CountingIt first{l.begin(), &steps}, last{l.end(), &steps};
    auto pos = std::lower_bound(first, last, 40000, [&](int a, int b) { ++compares; return a < b; });
    (void)pos;
    std::printf("n = %zu: comparisons = %ld, iterator steps = %ld\n", l.size(), compares, steps);
}
