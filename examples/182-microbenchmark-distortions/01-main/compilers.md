# 182 — Microbenchmark distortions: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** Both warn and both optimize the loop away at `-O2`; `-O0` times differ.

| | g++ | clang++ |
| --- | --- | --- |
| Warning (`-O0` and `-O2`) | `[-Wunused-but-set-variable=]` | `[-Wunused-but-set-variable]` |
| `bad.cpp` `-O0` (one run) | 689106066 ns | 1511379928 ns |
| `bad.cpp` `-O2` (one run) | 60 ns | 60 ns |
