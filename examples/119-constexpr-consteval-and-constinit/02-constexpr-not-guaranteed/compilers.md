# 119.02 — `constexpr`, `consteval`, and `constinit`: constexpr is not a guarantee: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++20`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `a = 0 (1 means compile time), b = 1` | `a = 0 (1 means compile time), b = 1` |
