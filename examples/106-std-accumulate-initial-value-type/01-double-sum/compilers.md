# 106.01 — `std::accumulate` initial-value type: truncation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both print `sum = 0 (expected 2)` at `-O0` and `-O2`. Only `clang-tidy` (`bugprone-fold-init-type`) reported it.
