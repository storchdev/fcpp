// std: c++17
#include <cstdio>

int counter = 0;
int next() { return ++counter; }

void show(int a, int b) { std::printf("a = %d, b = %d\n", a, b); }

int main() {
    int a = next();                            // a statement boundary fixes the order
    int b = next();
    show(a, b);
}
