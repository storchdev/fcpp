# 102.01 — `std::vector<bool>` specialization: `auto` deduces the proxy: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `flags[0] = 0 (wanted the original true)` | `flags[0] = 0 (wanted the original true)` |
