// std: c++17
#include <cstdio>

int main() {
    int i = 1;
    int first = i++;                           // one side effect per full-expression
    int second = ++i;
    int r = first + second;
    std::printf("r = %d, i = %d\n", r, i);
}
