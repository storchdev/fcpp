// std: c++17
// Access the member directly (the compiler knows it is packed) or copy through memcpy.
#include <cstdio>
#include <cstring>

struct __attribute__((packed)) Record {
    char tag;
    int value;
};

int main() {
    Record r{};
    int v = 3;
    std::memcpy(&r.value, &v, sizeof v);
    r.value += 1;                       // direct access: compiler emits an unaligned-safe access
    std::printf("%d\n", r.value);
}
