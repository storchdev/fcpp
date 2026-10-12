// std: c++17
// A packed member has no alignment guarantee; an `int*` to it promises 4-byte alignment.
#include <cstdio>

struct __attribute__((packed)) Record {
    char tag;
    int value;          // at offset 1
};

[[gnu::noinline]] void set(int* p, int v) { *p = v; }

int main() {
    Record r{};
    set(&r.value, 3);   // pointer to a misaligned int
    std::printf("%d\n", r.value);
}
