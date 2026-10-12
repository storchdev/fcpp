// std: c++17
#include <cstdio>

struct Maker {
    template <class U> U make() const { return U(); }
};

template <class M>
void g(const M& m) {
    int x = m.template make<int>();
    std::printf("%d\n", x);
}

int main() { g(Maker{}); }
