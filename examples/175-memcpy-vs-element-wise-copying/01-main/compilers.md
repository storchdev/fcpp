# 175 — `memcpy` vs. element-wise copying: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** No difference: neither compiler warns, plain runs abort with `double free detected in tcache 2` at `-O0` and `-O2` with both, and ASan reports `attempting double-free` at `-O0`, `-O1` and `-O2` with both.

