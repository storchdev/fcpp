// std: c++17
#include <cstdio>

struct Big {
    Big() { std::puts("construct"); }
    Big(const Big&) { std::puts("copy"); }
    Big(Big&&) noexcept { std::puts("move"); }
};

Big make() {
    Big b;
    return b;                                  // NRVO or implicit move; never a copy
}

int main() {
    Big x = make();
    (void)x;
}
