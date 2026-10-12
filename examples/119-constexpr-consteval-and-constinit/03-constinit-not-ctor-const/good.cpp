// std: c++20
#include <cstdio>

constexpr int compile_time_value() { return 42; }

constinit int g = compile_time_value();            // constant-initialised, but still modifiable at run time

int main() {
    g += 1;
    std::printf("%d\n", g);
}
