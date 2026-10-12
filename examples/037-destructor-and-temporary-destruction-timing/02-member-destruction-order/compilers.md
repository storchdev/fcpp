# 037.02 — Destructor and temporary destruction timing: member destruction order: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra` and `-fsanitize=address`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warnings | none at `-O0`; `-Wuninitialized` at `-O2` | none |
| No sanitizer, `-O0` | no output, exit status 0 | no output, exit status 0 |
| No sanitizer, `-O2` | crashes (core dumped) | no output, exit status 0 |
| ASan `-O0`, `-O1`, `-O2` | `heap-use-after-free` | `heap-use-after-free` |
