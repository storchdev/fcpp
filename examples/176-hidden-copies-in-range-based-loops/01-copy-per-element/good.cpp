// std: c++17
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
    for (const auto& h : v) sum += h.value;         // binds a reference: no copies
    std::printf("copies during the loop = %d, sum = %ld\n", Heavy::copies, sum);
}
