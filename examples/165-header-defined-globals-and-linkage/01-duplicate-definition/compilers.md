# 165.01 — Header-defined globals and linkage: duplicate definition: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17` `-Wall -Wextra`, `-O0` and `-O2`).** No difference: both fail at link time with `multiple definition of `counter'`; the wrapper line differs as described in `explanation.md`.

