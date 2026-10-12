# 128 — Exception guarantees and partially modified state: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `owner = bob, version = 0 (owner changed but version did not)` at `-O0` and `-O2`.
