# 034.02 — Lifetime of subobjects and base objects: a pure virtual call in a constructor: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none | none |
| Run, `-O0` and `-O2` | aborts: prints `pure virtual method called` and `terminate called without an active exception` (shell reports a core dump) | same |
