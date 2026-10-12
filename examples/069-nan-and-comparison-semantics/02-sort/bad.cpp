// std: c++17
// std::sort requires a strict weak ordering; operator< on doubles with a NaN is not one, so the result is unspecified garbage.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

int main(int argc, char**) {
    double nan = std::nan("") * argc;
    std::vector<double> v{5, 3, nan, 8, 1, nan, 9, 2, 7, 4, 6, 0, 10, 12, 11, 15, 14, 13, 17, 16};
    std::sort(v.begin(), v.end());             // UB: incomparability of NaN is not transitive
    for (double x : v) std::printf("%g ", x);
    std::printf("\nis_sorted: %d\n", std::is_sorted(v.begin(), v.end()));
}
