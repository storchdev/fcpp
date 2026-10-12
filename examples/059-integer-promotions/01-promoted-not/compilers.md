# 059.01 — Integer promotions: `~` on `uint8_t`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | `-Wsign-compare`: "comparison of promoted bitwise complement of an unsigned value with constant" | none |
| Output at `-O0` and `-O2` | `~mask is -16, not 0xF0` and `a + b = 300, sizeof(a + b) = 4` | same |
