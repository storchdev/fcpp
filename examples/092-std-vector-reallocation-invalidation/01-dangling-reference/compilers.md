# 092.01 — `std::vector` reallocation invalidation: dangling reference: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output without sanitizer, `-O0` and `-O2` | garbage for `first` | garbage for `first` |
| ASan, `-O0`, `-O1`, `-O2` | `heap-use-after-free` | `heap-use-after-free` |
| ASan summary source line | names the same source line | names the same source line |
