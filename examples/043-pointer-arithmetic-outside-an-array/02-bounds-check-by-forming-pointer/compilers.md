# 043.02 — Pointer arithmetic outside an array: checking a bound by forming the pointer: compiler comparison

**g++ vs clang++ (g++ 16.2.1, clang++ 23.1.1, `-std=c++17 -Wall -Wextra`, `-O0` and `-O2`).** Both print `fits(SIZE_MAX) = 1` at both levels. g++ emits `-Wmaybe-uninitialized` at `-O0` only (it is not about this bug); clang++ emits nothing. No sanitizer header is set because g++'s UBSan did not report this case (clang++'s reports a pointer overflow; see `explanation.md`).
