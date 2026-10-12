// std: c++17
#include <cstdio>
#include <cstdint>

int main() {
    std::int64_t cents = 0;                         // integer minor units: exact addition and comparison
    for (int i = 0; i < 10; ++i) cents += 10;
    std::printf("total = %lld.%02lld, total == 1.00: %d\n", (long long)(cents / 100), (long long)(cents % 100), (int)(cents == 100));
}
