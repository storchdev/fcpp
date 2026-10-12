# 043.02 — Pointer arithmetic outside an array: checking a bound by forming the pointer: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Output, `-O0` and `-O2` | `fits(SIZE_MAX) = 1` | `fits(SIZE_MAX) = 1` |
| Warnings | `-Wmaybe-uninitialized` at `-O0` only (unrelated to this bug) | none |
| UBSan | did not report this case, so no sanitizer header is set | reports a pointer overflow (see `explanation.md`) |
