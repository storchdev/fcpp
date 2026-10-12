// std: c++17
// Writing through a float* and reading through an int* to the same object violates the type-access rules.
#include <cstdio>

int set_and_read(int* i, float* f) {
    *i = 1;
    *f = 2.0f;        // the compiler may assume this cannot modify *i
    return *i;        // may return 1
}

int main() {
    int x = 0;
    int r = set_and_read(&x, reinterpret_cast<float*>(&x));   // same object accessed as int and float
    std::printf("r=%d x=%d\n", r, x);
}
