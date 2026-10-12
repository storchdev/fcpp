# 090.02 — `unique_ptr::release` vs. `reset`: `reset` dangles: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`; sanitizer also at `-O1`).** No difference: neither compiler warns, both print garbage for `level` at `-O0` and `-O2`, and ASan reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both.
