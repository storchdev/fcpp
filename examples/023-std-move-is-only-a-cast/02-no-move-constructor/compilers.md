# 023.02 — `std::move` is only a cast: the type has no move constructor: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `a=40 b=40` at `-O0` and `-O2`.
