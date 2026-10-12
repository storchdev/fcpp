// std: c++17
#include <cstdio>

int f(int n) {
    if (n > 0) return f(n - 1) + 1;                // recurse before the static's declaration is reached
    static int v = 0;
    return v;
}

int main() { std::printf("%d\n", f(1)); }
