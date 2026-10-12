// std: c++17
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

// NaN sorts after every number, and all NaNs are equivalent: a valid strict weak ordering.
bool nan_last(double a, double b) {
    if (std::isnan(a)) return false;
    if (std::isnan(b)) return true;
    return a < b;
}

int main(int argc, char**) {
    double nan = std::nan("") * argc;
    std::vector<double> v{5, 3, nan, 8, 1, nan, 9, 2, 7, 4, 6, 0, 10, 12, 11, 15, 14, 13, 17, 16};
    std::sort(v.begin(), v.end(), nan_last);
    for (double x : v) std::printf("%g ", x);
    std::printf("\nis_sorted: %d\n", std::is_sorted(v.begin(), v.end(), nan_last));
}
