// std: c++17
// Braces (or an extra pair of parentheses) cannot be parsed as a function declaration.
#include <cstdio>
#include <type_traits>

struct Clock {
    long now() const { return 42; }
};

struct Timer {
    explicit Timer(Clock c) : start(c.now()) { std::puts("Timer constructed"); }
    long start;
};

int main() {
    Timer t{Clock{}};   // always an object
    Timer u((Clock())); // extra parentheses also work, but are easy to "clean up" later

    static_assert(!std::is_function_v<decltype(t)>);
    std::printf("t.start = %ld, u.start = %ld\n", t.start, u.start);
}
