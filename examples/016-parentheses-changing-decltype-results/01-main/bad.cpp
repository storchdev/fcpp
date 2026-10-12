// std: c++17
// `decltype((m))` is a reference type, so an "extra" pair of parentheses turns a snapshot into an alias.
#include <cstdio>
#include <type_traits>

struct Config { int limit = 10; };

int main() {
    Config cfg;
    static_assert(std::is_same_v<decltype(cfg.limit), int>);     // unparenthesized member access: declared type
    static_assert(std::is_same_v<decltype((cfg.limit)), int&>);  // lvalue expression: T&

    using Snapshot = decltype((cfg.limit));  // int&, not int
    Snapshot before = cfg.limit;             // alias, not a copy
    cfg.limit = 99;
    std::printf("before = %d\n", before);    // 99, the "snapshot" changed
}
