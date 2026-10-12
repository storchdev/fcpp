# 140 — Lost wakeups and predicate synchronization: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `woken = 0` (after the 200 ms timeout) | `woken = 0` (after the 200 ms timeout) |
