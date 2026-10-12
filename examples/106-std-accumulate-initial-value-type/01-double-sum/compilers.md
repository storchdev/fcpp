# 106.01 — `std::accumulate` initial-value type: truncation: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `sum = 0 (expected 2)` | `sum = 0 (expected 2)` |
| `clang-tidy` `bugprone-fold-init-type` | reported it (the only tool that did) | reported it (the only tool that did) |
