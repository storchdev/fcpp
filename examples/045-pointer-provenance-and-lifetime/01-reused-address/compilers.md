# 045 — Pointer provenance and lifetime: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).**

| | g++ | clang++ |
| --- | --- | --- |
| Warning | `-Wuse-after-free=` at `-O0` and `-O2` | none |
| Output, `-O0` | `same address: *q=3` | `same address: *q=3` |
| Output, `-O2` | `same address: *q=2` | `different` |

This is the clearest case of the two compilers disagreeing about the same source: at `-O2` g++ takes the "same address" branch but reads `2`, and clang++ decides the pointers differ. The flag name ends in `=`, which the checker's `warning:` detection cannot express, so the g++ warning is not in `detection`.
