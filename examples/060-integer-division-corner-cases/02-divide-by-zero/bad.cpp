// std: c++17
// sanitize: undefined
// Integer division by zero is UB; for a runtime zero it usually traps (SIGFPE on x86).
#include <cstdio>

int average(int total, int count) { return total / count; }   // count == 0 is UB

int main(int argc, char**) {
    int count = argc - 1;                      // 0 when run without arguments
    std::printf("%d\n", average(10, count));
}
