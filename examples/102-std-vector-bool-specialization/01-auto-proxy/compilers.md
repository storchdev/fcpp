# 102.01 — `std::vector<bool>` specialization: `auto` deduces the proxy: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `flags[0] = 0 (wanted the original true)` at `-O0` and `-O2`.
