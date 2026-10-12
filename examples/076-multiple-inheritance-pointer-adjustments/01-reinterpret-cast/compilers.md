# 076.01 — Multiple inheritance pointer adjustments: `reinterpret_cast`: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | `-Wreinterpret-base-class`: "'reinterpret_cast' from class 'C *' to its base at non-zero offset 'B *' behaves differently from 'static_cast'" |
| Output at `-O0` and `-O2` | `right->b = 2, wrong->b = 1`, `offset of B in C: 4 bytes` | same |
