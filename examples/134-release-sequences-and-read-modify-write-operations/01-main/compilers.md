# 134 — Release sequences and read-modify-write operations: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-fsanitize=thread`, `-O0` and `-O2`).** No difference: neither compiler warns, both print `payload = 42` in a plain run, and TSan reported nothing at `-O0`, `-O1` or `-O2` with either compiler.

