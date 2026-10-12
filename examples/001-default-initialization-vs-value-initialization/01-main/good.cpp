// std: c++20
// Always make the initialization kind explicit.
#include <cstdio>
#include <memory>

struct Point {
    int x{};   // default member initializers: even `Point p;` is now safe
    int y{};
};

int main() {
    Point p;                              // safe now: members default to 0
    Point q{};                            // value-init, still fine
    auto buf = std::make_unique<int[]>(4);  // make_unique<T[]> value-initializes: all zeros

    // If you really want uninitialized storage for speed, say so (C++20):
    auto raw = std::make_unique_for_overwrite<int[]>(4);
    for (int i = 0; i < 4; ++i) raw[i] = i;  // write before you read

    std::printf("p=(%d,%d) q=(%d,%d) buf[0]=%d raw[3]=%d\n", p.x, p.y, q.x, q.y, buf[0], raw[3]);
}
