// std: c++17
#include <cmath>
#include <cstdio>
#include <map>

int main(int argc, char**) {
    double nan = std::nan("") * argc;
    std::printf("isnan(nan): %d\n", std::isnan(nan));   // test with isnan, never with ==

    std::map<double, int> m{{1.0, 10}, {2.0, 20}, {3.0, 30}};
    if (std::isnan(nan)) std::printf("rejecting NaN key\n");   // keep NaN out of ordered containers
    else m[nan] = 99;
    std::printf("size = %zu\n", m.size());
    for (auto& [k, v] : m) std::printf("%g -> %d\n", k, v);
}
