// std: c++17
// The same value has a different type depending on base and suffix, so the same comparison flips.
#include <cstdio>

const char* type_of(int)                { return "int"; }
const char* type_of(unsigned)           { return "unsigned int"; }
const char* type_of(long)               { return "long"; }
const char* type_of(unsigned long)      { return "unsigned long"; }
const char* type_of(long long)          { return "long long"; }

int main() {
    std::printf("2147483647  : %s\n", type_of(2147483647));
    std::printf("2147483648  : %s\n", type_of(2147483648));    // decimal: never unsigned without a suffix
    std::printf("0x80000000  : %s\n", type_of(0x80000000));    // hex: unsigned int fits, so it is chosen
    std::printf("-2147483648 : %s\n", type_of(-2147483648));   // unary minus applied to 2147483648 (a long)

    int status = -1;
    if (status < 0xFFFFFFFF) std::puts("-1 < 0xFFFFFFFF");     // false: status converts to unsigned
    if (status < 4294967295) std::puts("-1 < 4294967295");     // true: long can hold both
}
