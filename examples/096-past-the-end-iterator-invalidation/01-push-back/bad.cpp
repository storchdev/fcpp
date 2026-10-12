// std: c++17
// sanitize: address
// A cached end() is invalidated by any operation that reallocates; the loop compares against a dangling iterator.
#include <cstdio>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    v.shrink_to_fit();
    auto end = v.end();                            // cached for "efficiency"
    int visited = 0;
    for (auto it = v.begin(); it != end; ++it) {
        if (*it == 2) v.push_back(9);              // reallocates: it and end both dangle
        if (++visited > 20) break;
    }
    std::printf("visited = %d\n", visited);
}
