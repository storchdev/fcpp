# 158.01 — `std::optional` disengaged-state access: engaged vs. value: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `flag is set` at `-O0` and `-O2`.

