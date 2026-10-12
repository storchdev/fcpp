// std: c++17
// Unsigned arithmetic wraps modulo 2^N: size() - 1 on an empty vector is SIZE_MAX, and `i >= 0` is always true.
#include <cstdio>
#include <vector>

std::size_t last_index(const std::vector<int>& v) {
    return v.size() - 1;                    // empty: wraps to SIZE_MAX
}

int main() {
    std::vector<int> empty;
    std::printf("last_index(empty) = %zu\n", last_index(empty));

    int shown = 0;
    for (unsigned i = 3; i >= 0; --i) {     // always true: after 0 comes UINT_MAX
        std::printf("i = %u\n", i);
        if (++shown == 6) break;            // the cap only keeps this demo finite
    }
}
