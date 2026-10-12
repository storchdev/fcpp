# 034.02 — Lifetime of subobjects and base objects: a pure virtual call in a constructor: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** No difference: neither compiler warns, and both build a program that aborts at run time at `-O0` and `-O2`, printing `pure virtual method called` and `terminate called without an active exception` (and the shell reports a core dump).
