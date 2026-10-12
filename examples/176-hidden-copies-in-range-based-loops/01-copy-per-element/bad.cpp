// std: c++17
// `for (auto x : v)` copies each element; with an expensive type this is a copy per iteration.
#include <cstdio>
#include <vector>

struct Heavy {
    static inline int copies = 0;
    Heavy() = default;
    Heavy(const Heavy&) { ++copies; }
    int value = 1;
};

int main() {
    std::vector<Heavy> v(1000);
    Heavy::copies = 0;
    long sum = 0;
    for (auto h : v) sum += h.value;                // auto deduces Heavy: copy-constructs each element
    std::printf("copies during the loop = %d, sum = %ld\n", Heavy::copies, sum);
}
