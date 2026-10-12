// std: c++14
#include <cstdio>

int main() {
    int a[4] = {0, 0, 0, 0};
    int i = 0;
    int value = i++ + 10;                          // separate statements: the same in every standard
    a[i] = value;
    std::printf("a[0]=%d a[1]=%d i=%d\n", a[0], a[1], i);
}
