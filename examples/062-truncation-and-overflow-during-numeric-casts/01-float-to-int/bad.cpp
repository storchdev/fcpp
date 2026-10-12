// std: c++17
// sanitize: float-cast-overflow
// Converting a floating value that does not fit the destination integer type is UB.
#include <cstdio>

int to_int(double d) { return static_cast<int>(d); }   // UB if d, truncated, is outside int's range

int main(int argc, char**) {
    double big = 1e10 * argc;
    std::printf("%d\n", to_int(big));
}
