# 139 — Condition-variable spurious wakeups: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Output, `-O0` and `-O2` | `woke up, ready = 0` for `bad.cpp` | `woke up, ready = 0` for `bad.cpp` |
