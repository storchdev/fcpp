// std: c++17
#include <cstdio>
#include <set>

int main() {
    std::set<int> s;
    for (int i = 0; i < (1 << 16); ++i) s.insert(s.end(), i);
    auto it = s.lower_bound(40000);                // O(log n) tree descent: the container knows its structure
    std::printf("n = %zu: lower_bound = %d\n", s.size(), *it);
}
