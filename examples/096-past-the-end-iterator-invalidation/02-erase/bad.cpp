// std: c++17
// erase invalidates the iterators at and after the erased element, including end(): a cached end overshoots.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4};
    auto last = v.end();                           // cached
    v.erase(v.begin());                            // end() moved back by one, last did not
    for (auto it = v.begin(); it != last; ++it) std::printf("%d ", *it);   // one element past the real end
    std::printf("\n");
}
