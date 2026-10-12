// std: c++17
// Re-entering the initialization of a function-local static from the same thread is undefined behavior.
#include <cstdio>

int f(int n) {
    static int v = n > 0 ? f(n - 1) + 1 : 0;       // the initializer calls f again, re-entering this declaration
    return v;
}

int main() { std::printf("%d\n", f(1)); }
