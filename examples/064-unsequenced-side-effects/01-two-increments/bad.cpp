// std: c++17
// Two unsequenced modifications of the same scalar in one expression are UB.
#include <cstdio>

int main() {
    int i = 1;
    int r = i++ + ++i;                         // operands of + are unsequenced: UB
    std::printf("r = %d, i = %d\n", r, i);
}
