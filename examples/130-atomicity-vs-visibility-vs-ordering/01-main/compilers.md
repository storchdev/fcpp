# 130 — Atomicity vs. visibility vs. ordering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference in kind: neither compiler warns, and both lose roughly half of the updates at `-O0` and `-O2` (the counts above vary per run).

