# 119.02 — `constexpr`, `consteval`, and `constinit`: constexpr is not a guarantee: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `a = 0 (1 means compile time), b = 1` at `-O0` and `-O2`.

