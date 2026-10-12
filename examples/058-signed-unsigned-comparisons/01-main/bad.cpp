// std: c++17
// In `int < unsigned` the int is converted to unsigned, so -1 becomes UINT_MAX and compares as larger.
#include <cstdio>
#include <vector>

int main() {
    int a = -1;
    unsigned b = 1;
    std::printf("-1 < 1u is %s\n", a < b ? "true" : "false");          // false

    std::vector<int> v{1, 2, 3};
    int idx = -1;
    if (idx < v.size())                                                // idx converted to size_t
        std::printf("idx %d is in range\n", idx);
    else
        std::printf("idx %d is out of range (wrong reason)\n", idx);
}
