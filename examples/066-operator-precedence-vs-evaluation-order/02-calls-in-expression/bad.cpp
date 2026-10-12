// std: c++17
// Precedence decides how operands group, not the order in which the operand calls run.
#include <cstdio>

int trace(char name, int value) {
    std::printf("%c ", name);
    return value;
}

int main() {
    int r = trace('a', 1) + trace('b', 2) * trace('c', 3);   // grouping: a + (b * c); call order unspecified
    std::printf("-> %d\n", r);
}
