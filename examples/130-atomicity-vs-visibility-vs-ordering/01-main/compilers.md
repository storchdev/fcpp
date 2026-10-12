# 130 — Atomicity vs. visibility vs. ordering: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | loses roughly half of the updates (counts vary per run) | loses roughly half of the updates (counts vary per run) |
