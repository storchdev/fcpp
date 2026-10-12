# 106.02 — `std::accumulate` initial-value type: overflow: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=undefined`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | `sum = -2147483648` | `sum = -2147483648` |
| UBSan, `-O0`, `-O1`, `-O2` | `signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'` | `signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'` |
