# 175 — `memcpy` vs. element-wise copying: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run without sanitizer, `-O0` and `-O2` | aborts with `double free detected in tcache 2` | aborts with `double free detected in tcache 2` |
| ASan, `-O0`, `-O1`, `-O2` | `attempting double-free` | `attempting double-free` |
