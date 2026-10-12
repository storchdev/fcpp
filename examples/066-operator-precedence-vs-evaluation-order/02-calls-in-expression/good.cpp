// std: c++17
#include <cstdio>

int trace(char name, int value) {
    std::printf("%c ", name);
    return value;
}

int main() {
    int a = trace('a', 1);                     // if the order matters, make it a sequence of statements
    int b = trace('b', 2);
    int c = trace('c', 3);
    int r = a + b * c;
    std::printf("-> %d\n", r);
}
