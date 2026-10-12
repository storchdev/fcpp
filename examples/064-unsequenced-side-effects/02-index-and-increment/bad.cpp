// std: c++14
// `a[i] = i++` is unsequenced before C++17 (UB) and well-defined from C++17 on.
#include <cstdio>

int main() {
    int a[4] = {0, 0, 0, 0};
    int i = 0;
    a[i] = i++ + 10;                               // C++14: UB; C++17: the right operand is sequenced first
    std::printf("a[0]=%d a[1]=%d i=%d\n", a[0], a[1], i);
}
