// std: c++17
// NaN is unordered: it is neither less than nor greater than anything, so an ordered container treats it as equivalent to whatever it is compared with.
#include <cmath>
#include <cstdio>
#include <map>

int main(int argc, char**) {
    double nan = std::nan("") * argc;
    std::printf("nan == nan: %d\n", nan == nan);   // 0
    std::printf("nan < 1.0: %d, nan > 1.0: %d\n", nan < 1.0, nan > 1.0);   // 0, 0

    std::map<double, int> m{{1.0, 10}, {2.0, 20}, {3.0, 30}};
    m[nan] = 99;                               // the map "finds" an existing key instead of inserting
    std::printf("size = %zu\n", m.size());
    for (auto& [k, v] : m) std::printf("%g -> %d\n", k, v);
}
