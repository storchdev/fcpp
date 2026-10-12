// std: c++17
// Drop the parentheses to get the declared type, or use std::remove_reference_t / auto to be explicit.
#include <cstdio>
#include <type_traits>

struct Config { int limit = 10; };

int main() {
    Config cfg;
    using Snapshot = decltype(cfg.limit);    // int
    Snapshot before = cfg.limit;
    cfg.limit = 99;
    std::printf("before = %d\n", before);    // 10

    static_assert(std::is_same_v<std::remove_reference_t<decltype((cfg.limit))>, int>);
}
