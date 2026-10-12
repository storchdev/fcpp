// std: c++17
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdio>

// Floating-point results depend on grouping, so compare them with a tolerance scaled to the
// magnitude of the operands that were involved, never with ==.
bool nearly_equal(double x, double y, double scale) {
    return std::fabs(x - y) <= 4 * DBL_EPSILON * scale;
}

int main(int argc, char**) {
    double big = 1e16 * argc;
    double a = big, b = -big, c = 1.0;
    double left = (a + b) + c;                 // 1
    double right = a + (b + c);                // 0
    double scale = std::max({std::fabs(a), std::fabs(b), std::fabs(c)});
    std::printf("left = %g, right = %g, equal with == : %d\n", left, right, left == right);
    std::printf("nearly equal at the scale of the operands: %d\n", nearly_equal(left, right, scale));
}
