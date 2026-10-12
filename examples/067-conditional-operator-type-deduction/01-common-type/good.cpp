// std: c++17
#include <cstdio>

int main(int argc, char**) {
    int idx = -1;
    unsigned n = 5;
    bool pick = argc > 0;
    long long m = pick ? static_cast<long long>(idx) : static_cast<long long>(n);   // one type that holds both ranges
    std::printf("m = %lld, m > 100 is %s\n", m, m > 100 ? "true" : "false");
}
