// std: c++17
// Decimal prices are not exactly representable in binary floating point: sums and comparisons drift.
#include <cstdio>

int main() {
    double total = 0.0;
    for (int i = 0; i < 10; ++i) total += 0.10;     // ten dimes
    std::printf("total = %.17g, total == 1.00: %d\n", total, (int)(total == 1.00));
    std::printf("0.1 + 0.2 == 0.3: %d\n", (int)(0.1 + 0.2 == 0.3));
}
