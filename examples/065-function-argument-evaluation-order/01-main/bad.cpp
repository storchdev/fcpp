// std: c++17
// Arguments are evaluated in an unspecified order (indeterminately sequenced, not left to right).
#include <cstdio>

int counter = 0;
int next() { return ++counter; }

void show(int a, int b) { std::printf("a = %d, b = %d\n", a, b); }

int main() {
    show(next(), next());                      // a = 1, b = 2 or a = 2, b = 1
}
