// std: c++17
// Capture by value; a mutable lambda owns and updates its own copy.
#include <cstdio>
#include <functional>

std::function<int()> make_counter(int start) {
    return [count = start]() mutable { return ++count; };
}

int main() {
    auto next = make_counter(10);
    int a = next();      // separate statements: argument evaluation order is unspecified
    int b = next();
    std::printf("%d %d\n", a, b);
}
