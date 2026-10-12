// std: c++17
// sanitize: address
// Memory from new[] must be released with delete[].
#include <cstdio>

int main() {
    int* values = new int[4]{1, 2, 3, 4};
    std::printf("%d\n", values[3]);
    delete values;                          // UB: should be delete[]
}
