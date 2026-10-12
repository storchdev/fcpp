# 023.01 — `std::move` is only a cast: the receiver cannot move: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `inspect: 40 bytes`, `after inspect: 40 bytes` and `n=5 m=5` | `inspect: 40 bytes`, `after inspect: 40 bytes` and `n=5 m=5` |
