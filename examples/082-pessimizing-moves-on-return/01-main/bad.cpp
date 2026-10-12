// std: c++17
// return std::move(local) disables NRVO and forces a move.
#include <cstdio>
#include <utility>

struct Big {
    Big() { std::puts("construct"); }
    Big(const Big&) { std::puts("copy"); }
    Big(Big&&) noexcept { std::puts("move"); }
};

Big make() {
    Big b;
    return std::move(b);                       // not an elision candidate any more: move constructor runs
}

int main() {
    Big x = make();
    (void)x;
}
