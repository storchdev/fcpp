# 085 — Exception safety of move constructors: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `copies=127 moves=0` | `copies=127 moves=0` |
| `clang-tidy` `performance-noexcept-move-constructor` | reported it (the only tool that did) | reported it (the only tool that did) |
