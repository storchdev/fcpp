// std: c++17
// The branches of ?: are converted to a common type: int and unsigned int meet at unsigned int.
#include <cstdio>

int main(int argc, char**) {
    int idx = -1;
    unsigned n = 5;
    bool pick = argc > 0;
    auto m = pick ? idx : n;                   // type is unsigned int: idx is converted, -1 becomes 4294967295
    std::printf("m = %u, m > 100 is %s\n", m, m > 100 ? "true" : "false");
}
