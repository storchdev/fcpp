# 174 — Custom allocator and `std::pmr` lifetime errors: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=address`, `-O0` and `-O2`).** No difference: neither compiler warns, plain runs abort at `-O0` and print `v[999] = 999` at `-O2` with both, and ASan reports `heap-use-after-free` at `-O0`, `-O1` and `-O2` with both.

