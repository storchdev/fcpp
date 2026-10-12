// std: c++17
#include <cstdio>
#include <utility>

struct Tracker {
    Tracker() = default;
    Tracker(const Tracker&) { std::puts("copy"); }
    Tracker(Tracker&&) noexcept { std::puts("move"); }
};

struct WithDtor {
    Tracker t;
    WithDtor() = default;
    WithDtor(const WithDtor&) = default;
    WithDtor(WithDtor&&) = default;            // rule of five: say what you want
    ~WithDtor() { std::puts("cleanup"); }
};

int main() {
    WithDtor w;
    WithDtor w2 = std::move(w);                // "move"
}
